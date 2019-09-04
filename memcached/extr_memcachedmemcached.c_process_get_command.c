#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_33__ {char* value; size_t length; } ;
typedef  TYPE_4__ token_t ;
typedef  int /*<<< orphan*/  rel_time_t ;
struct TYPE_34__ {size_t nkey; int nbytes; int nsuffix; int it_flags; size_t slabs_clsid; } ;
typedef  TYPE_5__ item ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_35__ {char sfd; int ileft; int suffixleft; scalar_t__ msgcurr; int /*<<< orphan*/  transport; int /*<<< orphan*/  suffixlist; int /*<<< orphan*/  suffixcurr; TYPE_5__** ilist; TYPE_5__** icurr; TYPE_3__* thread; } ;
typedef  TYPE_6__ conn ;
struct TYPE_36__ {int verbose; scalar_t__ inline_ascii_response; scalar_t__ detail_enabled; } ;
struct TYPE_31__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  get_cmds; int /*<<< orphan*/  get_misses; int /*<<< orphan*/  touch_misses; int /*<<< orphan*/  touch_cmds; int /*<<< orphan*/ * lru_hits; TYPE_1__* slab_stats; } ;
struct TYPE_32__ {TYPE_2__ stats; } ;
struct TYPE_30__ {int /*<<< orphan*/  touch_hits; } ;

/* Variables and functions */
 scalar_t__ IS_UDP (int /*<<< orphan*/ ) ; 
 int ITEM_CHUNKED ; 
 size_t ITEM_clsid (TYPE_5__*) ; 
 char* ITEM_data (TYPE_5__*) ; 
 int /*<<< orphan*/  ITEM_get_cas (TYPE_5__*) ; 
 char* ITEM_key (TYPE_5__*) ; 
 char* ITEM_suffix (TYPE_5__*) ; 
 size_t KEY_MAX_LENGTH ; 
 size_t KEY_TOKEN ; 
 int /*<<< orphan*/  MAX_TOKENS ; 
 int /*<<< orphan*/  MEMCACHED_COMMAND_GET (char,char*,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _ascii_get_expand_ilist (TYPE_6__*,int) ; 
 char* _ascii_get_suffix_buf (TYPE_6__*,int) ; 
 scalar_t__ add_chunked_item_iovs (TYPE_6__*,TYPE_5__*,int) ; 
 scalar_t__ add_iov (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ build_udp_headers (TYPE_6__*) ; 
 int /*<<< orphan*/  conn_mwrite ; 
 int /*<<< orphan*/  conn_release_items (TYPE_6__*) ; 
 int /*<<< orphan*/  conn_set_state (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  item_remove (TYPE_5__*) ; 
 TYPE_5__* limited_get (char*,size_t,TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int make_ascii_get_suffix (char*,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  out_of_memory (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  out_string (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strtol (char*,int /*<<< orphan*/ *) ; 
 TYPE_8__ settings ; 
 int /*<<< orphan*/  stats_prefix_record_get (char*,size_t,int) ; 
 int /*<<< orphan*/  stderr ; 
 size_t tokenize_command (char*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void process_get_command(conn *c, token_t *tokens, size_t ntokens, bool return_cas, bool should_touch) {
    char *key;
    size_t nkey;
    int i = 0;
    int si = 0;
    item *it;
    token_t *key_token = &tokens[KEY_TOKEN];
    char *suffix;
    int32_t exptime_int = 0;
    rel_time_t exptime = 0;
    bool fail_length = false;
    assert(c != NULL);

    if (should_touch) {
        // For get and touch commands, use first token as exptime
        if (!safe_strtol(tokens[1].value, &exptime_int)) {
            out_string(c, "CLIENT_ERROR invalid exptime argument");
            return;
        }
        key_token++;
        exptime = realtime(exptime_int);
    }

    do {
        while(key_token->length != 0) {

            key = key_token->value;
            nkey = key_token->length;

            if (nkey > KEY_MAX_LENGTH) {
                fail_length = true;
                goto stop;
            }

            it = limited_get(key, nkey, c, exptime, should_touch);
            if (settings.detail_enabled) {
                stats_prefix_record_get(key, nkey, NULL != it);
            }
            if (it) {
                if (_ascii_get_expand_ilist(c, i) != 0) {
                    item_remove(it);
                    goto stop;
                }

                /*
                 * Construct the response. Each hit adds three elements to the
                 * outgoing data list:
                 *   "VALUE "
                 *   key
                 *   " " + flags + " " + data length + "\r\n" + data (with \r\n)
                 */

                if (return_cas || !settings.inline_ascii_response)
                {
                  MEMCACHED_COMMAND_GET(c->sfd, ITEM_key(it), it->nkey,
                                        it->nbytes, ITEM_get_cas(it));
                  int nbytes;
                  suffix = _ascii_get_suffix_buf(c, si);
                  if (suffix == NULL) {
                      item_remove(it);
                      goto stop;
                  }
                  si++;
                  nbytes = it->nbytes;
                  int suffix_len = make_ascii_get_suffix(suffix, it, return_cas, nbytes);
                  if (add_iov(c, "VALUE ", 6) != 0 ||
                      add_iov(c, ITEM_key(it), it->nkey) != 0 ||
                      (settings.inline_ascii_response && add_iov(c, ITEM_suffix(it), it->nsuffix - 2) != 0) ||
                      add_iov(c, suffix, suffix_len) != 0)
                      {
                          item_remove(it);
                          goto stop;
                      }
#ifdef EXTSTORE
                  if (it->it_flags & ITEM_HDR) {
                      if (_get_extstore(c, it, c->iovused-3, 4) != 0) {
                          pthread_mutex_lock(&c->thread->stats.mutex);
                          c->thread->stats.get_oom_extstore++;
                          pthread_mutex_unlock(&c->thread->stats.mutex);

                          item_remove(it);
                          goto stop;
                      }
                  } else if ((it->it_flags & ITEM_CHUNKED) == 0) {
#else
                  if ((it->it_flags & ITEM_CHUNKED) == 0) {
#endif
                      add_iov(c, ITEM_data(it), it->nbytes);
                  } else if (add_chunked_item_iovs(c, it, it->nbytes) != 0) {
                      item_remove(it);
                      goto stop;
                  }
                }
                else
                {
                  MEMCACHED_COMMAND_GET(c->sfd, ITEM_key(it), it->nkey,
                                        it->nbytes, ITEM_get_cas(it));
                  if (add_iov(c, "VALUE ", 6) != 0 ||
                      add_iov(c, ITEM_key(it), it->nkey) != 0)
                      {
                          item_remove(it);
                          goto stop;
                      }
                  if ((it->it_flags & ITEM_CHUNKED) == 0)
                      {
                          if (add_iov(c, ITEM_suffix(it), it->nsuffix + it->nbytes) != 0)
                          {
                              item_remove(it);
                              goto stop;
                          }
                      } else if (add_iov(c, ITEM_suffix(it), it->nsuffix) != 0 ||
                                 add_chunked_item_iovs(c, it, it->nbytes) != 0) {
                          item_remove(it);
                          goto stop;
                      }
                }


                if (settings.verbose > 1) {
                    int ii;
                    fprintf(stderr, ">%d sending key ", c->sfd);
                    for (ii = 0; ii < it->nkey; ++ii) {
                        fprintf(stderr, "%c", key[ii]);
                    }
                    fprintf(stderr, "\n");
                }

                /* item_get() has incremented it->refcount for us */
                pthread_mutex_lock(&c->thread->stats.mutex);
                if (should_touch) {
                    c->thread->stats.touch_cmds++;
                    c->thread->stats.slab_stats[ITEM_clsid(it)].touch_hits++;
                } else {
                    c->thread->stats.lru_hits[it->slabs_clsid]++;
                    c->thread->stats.get_cmds++;
                }
                pthread_mutex_unlock(&c->thread->stats.mutex);
#ifdef EXTSTORE
                /* If ITEM_HDR, an io_wrap owns the reference. */
                if ((it->it_flags & ITEM_HDR) == 0) {
                    *(c->ilist + i) = it;
                    i++;
                }
#else
                *(c->ilist + i) = it;
                i++;
#endif
            } else {
                pthread_mutex_lock(&c->thread->stats.mutex);
                if (should_touch) {
                    c->thread->stats.touch_cmds++;
                    c->thread->stats.touch_misses++;
                } else {
                    c->thread->stats.get_misses++;
                    c->thread->stats.get_cmds++;
                }
                MEMCACHED_COMMAND_GET(c->sfd, key, nkey, -1, 0);
                pthread_mutex_unlock(&c->thread->stats.mutex);
            }

            key_token++;
        }

        /*
         * If the command string hasn't been fully processed, get the next set
         * of tokens.
         */
        if(key_token->value != NULL) {
            ntokens = tokenize_command(key_token->value, tokens, MAX_TOKENS);
            key_token = tokens;
        }

    } while(key_token->value != NULL);
stop:

    c->icurr = c->ilist;
    c->ileft = i;
    if (return_cas || !settings.inline_ascii_response) {
        c->suffixcurr = c->suffixlist;
        c->suffixleft = si;
    }

    if (settings.verbose > 1)
        fprintf(stderr, ">%d END\n", c->sfd);

    /*
        If the loop was terminated because of out-of-memory, it is not
        reliable to add END\r\n to the buffer, because it might not end
        in \r\n. So we send SERVER_ERROR instead.
    */
    if (key_token->value != NULL || add_iov(c, "END\r\n", 5) != 0
        || (IS_UDP(c->transport) && build_udp_headers(c) != 0)) {
        if (fail_length) {
            out_string(c, "CLIENT_ERROR bad command line format");
        } else {
            out_of_memory(c, "SERVER_ERROR out of memory writing get response");
        }
        conn_release_items(c);
    }
    else {
        conn_set_state(c, conn_mwrite);
        c->msgcurr = 0;
    }
}