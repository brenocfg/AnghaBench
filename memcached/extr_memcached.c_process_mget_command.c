#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_36__ {size_t length; char* value; } ;
typedef  TYPE_4__ token_t ;
struct _meta_flags {int value; scalar_t__ locked; int /*<<< orphan*/  no_update; scalar_t__ vivify; int /*<<< orphan*/  no_reply; int /*<<< orphan*/  member_0; } ;
struct TYPE_37__ {int it_flags; int exptime; int nbytes; int time; int nkey; size_t slabs_clsid; } ;
typedef  TYPE_5__ item ;
typedef  int int32_t ;
struct TYPE_38__ {char* wbuf; int iovused; TYPE_3__* thread; int /*<<< orphan*/  sfd; int /*<<< orphan*/  write_and_go; TYPE_5__* item; int /*<<< orphan*/  noreply; } ;
typedef  TYPE_6__ conn ;
struct TYPE_34__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  get_cmds; int /*<<< orphan*/  get_misses; int /*<<< orphan*/  touch_misses; int /*<<< orphan*/  touch_cmds; int /*<<< orphan*/ * lru_hits; TYPE_1__* slab_stats; int /*<<< orphan*/  get_oom_extstore; } ;
struct TYPE_35__ {TYPE_2__ stats; } ;
struct TYPE_33__ {int /*<<< orphan*/  touch_hits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DONT_UPDATE ; 
 int /*<<< orphan*/  FLAGS_SIZE (TYPE_5__*) ; 
 int ITEM_CHUNKED ; 
 int ITEM_FETCHED ; 
 int ITEM_HDR ; 
 int ITEM_STALE ; 
 int ITEM_TOKEN_SENT ; 
 size_t ITEM_clsid (TYPE_5__*) ; 
 char* ITEM_data (TYPE_5__*) ; 
 int /*<<< orphan*/  ITEM_get_cas (TYPE_5__*) ; 
 char* ITEM_key (TYPE_5__*) ; 
 scalar_t__ ITEM_suffix (TYPE_5__*) ; 
 size_t KEY_MAX_LENGTH ; 
 size_t KEY_TOKEN ; 
 int /*<<< orphan*/  MEMCACHED_COMMAND_GET (int /*<<< orphan*/ ,char*,size_t,int,int /*<<< orphan*/ ) ; 
 size_t MFLAG_MAX_OPAQUE_LENGTH ; 
 size_t MFLAG_MAX_OPT_LENGTH ; 
 scalar_t__ _get_extstore (TYPE_6__*,TYPE_5__*,int,int) ; 
 int _meta_flag_preparse (char*,size_t,struct _meta_flags*) ; 
 int /*<<< orphan*/  add_chunked_item_iovs (TYPE_6__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  add_iov (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_new_cmd ; 
 int /*<<< orphan*/  conn_set_state (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_write ; 
 int current_time ; 
 int /*<<< orphan*/  do_item_bump (TYPE_6__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  do_item_link (TYPE_5__*,int) ; 
 int /*<<< orphan*/  do_item_remove (TYPE_5__*) ; 
 TYPE_5__* item_alloc (char*,size_t,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  item_remove (TYPE_5__*) ; 
 int /*<<< orphan*/  item_unlock (int) ; 
 char* itoa_u32 (int,char*) ; 
 char* itoa_u64 (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* limited_get (char*,size_t,TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* limited_get_locked (char*,size_t,TYPE_6__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  out_errstring (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  out_string (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 void* realtime (int) ; 
 int /*<<< orphan*/  safe_strtol (char*,int*) ; 

__attribute__((used)) static void process_mget_command(conn *c, token_t *tokens, const size_t ntokens) {
    char *key;
    size_t nkey;
    item *it;
    char *opts;
    char *fp = NULL;
    char *p = c->wbuf;
    size_t olen;
    unsigned int i = 0;
    int32_t rtokens = 0; // remaining tokens available.
    struct _meta_flags of = {0}; // option bitflags.
    uint32_t hv; // cached hash value for unlocking an item.
    bool failed = false;
    bool item_created = false;
    bool won_token = false;
    bool ttl_set = false;
    char *errstr;

    assert(c != NULL);

    if (tokens[KEY_TOKEN].length > KEY_MAX_LENGTH) {
        out_errstring(c, "CLIENT_ERROR bad command line format");
        return;
    }

    key = tokens[KEY_TOKEN].value;
    nkey = tokens[KEY_TOKEN].length;

    // NOTE: final token has length == 0.
    // KEY_TOKEN == 1. 0 is command.
    rtokens = 3; // cmd, key, final.

    if (ntokens == 3) {
        // Default flag options. Might not be the best idea.
        opts = "sftv";
        olen = 4;
    } else {
        // need to parse out the options.
        opts = tokens[KEY_TOKEN + 1].value;
        olen = tokens[KEY_TOKEN + 1].length;
        rtokens++;
    }

    if (olen > MFLAG_MAX_OPT_LENGTH) {
        out_errstring(c, "CLIENT_ERROR options flags are too long");
        return;
    }

    // Copy opts into wbuf and advance pointer.
    // We return the initial options + extra indicator flags.
    // we reserve 4 bytes in front of the buffer, for up to three extra flags
    // we can tag plus the initial space.
    // This could be simpler by adding two iov's for the header line, but this
    // is a hot path so trying to keep those to a minimum.
    fp = c->wbuf + 6;
    memcpy(fp, opts, olen);
    p = fp + olen;
    fp--; // next token, or final space, goes here.

    // scrubs duplicated options and sets flags for how to load the item.
    int mfres = _meta_flag_preparse(opts, olen, &of);

    if (mfres + rtokens != ntokens) {
        if (mfres == -1) {
            out_errstring(c, "CLIENT_ERROR invalid or duplicate flag");
        } else {
            out_errstring(c, "CLIENT_ERROR incorrect number of tokens supplied");
        }
        return;
    }
    rtokens = KEY_TOKEN + 2;
    c->noreply = of.no_reply;

    // TODO: need to indicate if the item was overflowed or not?
    // I think we do, since an overflow shouldn't trigger an alloc/replace.
    if (!of.locked) {
        it = limited_get(key, nkey, c, 0, false, !of.no_update);
    } else {
        // If we had to lock the item, we're doing our own bump later.
        it = limited_get_locked(key, nkey, c, DONT_UPDATE, &hv);
    }

    if (it == NULL && of.vivify) {
        // Fill in the exptime during parsing later.
        it = item_alloc(key, nkey, 0, realtime(0), 2);
        // We don't actually need any of do_store_item's logic:
        // - already fetched and missed an existing item.
        // - lock is still held.
        // - not append/prepend/replace
        // - not testing CAS
        if (it != NULL) {
            // I look forward to the day I get rid of this :)
            memcpy(ITEM_data(it), "\r\n", 2);
            // NOTE: This initializes the CAS value.
            do_item_link(it, hv);
            item_created = true;
        }
    }

    // don't have to check result of add_iov() since the iov size defaults are
    // enough.
    if (it) {
        int32_t exptime_int = 0;

        // Has this item already sent a token?
        // Important to do this here so we don't send W with Z.
        // Isn't critical, but easier for client authors to understand.
        if (it->it_flags & ITEM_TOKEN_SENT) {
            *fp = 'Z';
            fp--;
        }
        if (it->it_flags & ITEM_STALE) {
            *fp = 'X';
            fp--;
            // FIXME: think hard about this. is this a default, or a flag?
            if ((it->it_flags & ITEM_TOKEN_SENT) == 0) {
                // If we're stale but no token already sent, now send one.
                won_token = true;
            }
        }

        for (i = 0; i < olen; i++) {
            switch (opts[i]) {
                case 'T':
                    ttl_set = true;
                    if (!safe_strtol(tokens[rtokens].value, &exptime_int)) {
                        errstr = "CLIENT_ERROR bad tokens in command line format";
                        goto error;
                    }
                    // FIXME: check for < 0, or stoul and cast here.
                    it->exptime = realtime(exptime_int);
                    rtokens++;
                    break;
                case 'N':
                    if (item_created) {
                        if (!safe_strtol(tokens[rtokens].value, &exptime_int)) {
                            errstr = "CLIENT_ERROR bad tokens in command line format";
                            goto error;
                        }
                        // FIXME: check for < 0, or stoul and cast here.
                        it->exptime = realtime(exptime_int);
                        won_token = true;
                    }
                    rtokens++; // always consume the token.
                    break;
                case 'R':
                    // If we haven't autovivified and supplied token is less
                    // than current TTL, mark a win.
                    if ((it->it_flags & ITEM_TOKEN_SENT) == 0
                            && !item_created
                            && it->exptime != 0) {
                        if (!safe_strtol(tokens[rtokens].value, &exptime_int)) {
                            errstr = "CLIENT_ERROR bad tokens in command line format";
                            goto error;
                        }

                        if (it->exptime - current_time < exptime_int) {
                            won_token = true;
                        }
                    }
                    rtokens++;
                    break;
                case 's':
                    *p = ' ';
                    p = itoa_u32(it->nbytes-2, p+1);
                    break;
                case 't':
                    // TODO: ensure this is correct for autoviv case.
                    // or, I guess users can put N before t?
                    // TTL remaining as of this request.
                    // needs to be relative because server clocks may not be in sync.
                    *p = ' ';
                    if (it->exptime == 0) {
                        *(p+1) = '-';
                        *(p+2) = '1';
                        p += 3;
                    } else {
                        p = itoa_u32(it->exptime - current_time, p+1);
                    }
                    break;
                case 'c':
                    *p = ' ';
                    p = itoa_u64(ITEM_get_cas(it), p+1);
                    break;
                case 'v':
                    of.value = 1;
                    break;
                case 'f':
                    *p = ' ';
                    if (FLAGS_SIZE(it) == 0) {
                        *(p+1) = '0';
                        p += 2;
                    } else {
                        p = itoa_u32(*((uint32_t *) ITEM_suffix(it)), p+1);
                    }
                    break;
                case 'l':
                    *p = ' ';
                    p = itoa_u32(current_time - it->time, p+1);
                    break;
                case 'h':
                    *p = ' ';
                    if (it->it_flags & ITEM_FETCHED) {
                        *(p+1) = '1';
                    } else {
                        *(p+1) = '0';
                    }
                    p += 2;
                    break;
                case 'O':
                    if (tokens[rtokens].length > MFLAG_MAX_OPAQUE_LENGTH) {
                        errstr = "CLIENT_ERROR opaque token too long";
                        goto error;
                    }
                    *p = ' ';
                    memcpy(p+1, tokens[rtokens].value, tokens[rtokens].length);
                    p += tokens[rtokens].length + 1;
                    rtokens++;
                    break;
                case 'k':
                    *p = ' ';
                    memcpy(p+1, ITEM_key(it), it->nkey);
                    p += it->nkey + 1;
                    break;
            }
        }

        if (won_token) {
            // Mark a win into the flag buffer.
            *fp = 'W';
            fp--; // walk backwards for next token.
            it->it_flags |= ITEM_TOKEN_SENT;
        }

        // TODO: Benchmark unlocking here vs later. _get_extstore() could be
        // intensive so probably better to unlock here after we're done
        // fiddling with the item header.

        *p = '\r';
        *(p+1) = '\n';
        *(p+2) = '\0';
        p += 2;
        // tag initial space to the front of the buffer, ahead of any extra
        // flags that were added.
        *fp = ' ';
        *(fp-1) = 'A';
        *(fp-2) = 'V';
        fp -= 2;
        // finally, chain in the buffer.
        // fp includes the flags.
        add_iov(c, fp, p - fp);

        if (of.value) {
#ifdef EXTSTORE
            if (it->it_flags & ITEM_HDR) {
                // this bizarre interface is instructing _get_extstore() to
                // "walk back and zero out" this many iovec's on an internal
                // miss. kills the VALUE + key + header stitched above.
                int iovcnt = 2;
                int iovst = c->iovused - 1;

                if (_get_extstore(c, it, iovst, iovcnt) != 0) {
                    pthread_mutex_lock(&c->thread->stats.mutex);
                    c->thread->stats.get_oom_extstore++;
                    pthread_mutex_unlock(&c->thread->stats.mutex);

                    failed = true;
                }
            } else if ((it->it_flags & ITEM_CHUNKED) == 0) {
                add_iov(c, ITEM_data(it), it->nbytes);
            } else {
                add_chunked_item_iovs(c, it, it->nbytes);
            }
#else
            if ((it->it_flags & ITEM_CHUNKED) == 0) {
                add_iov(c, ITEM_data(it), it->nbytes);
            } else {
                add_chunked_item_iovs(c, it, it->nbytes);
            }
#endif
        }

        if (!c->noreply) {
            add_iov(c, "EN\r\n", 4);
        }

        // need to hold the ref at least because of the key above.
#ifdef EXTSTORE
        if (!failed) {
            if ((it->it_flags & ITEM_HDR) != 0 && of.value) {
                // Only have extstore clean if header and returning value.
                c->item = NULL;
            } else {
                c->item = it;
            }
        } else {
            if (of.locked) {
                do_item_remove(it);
            } else {
                item_remove(it);
            }
        }
#else
        c->item = it;
#endif
    } else {
        failed = true;
    }

    if (of.locked) {
        // Delayed bump so we could get fetched/last access time/etc.
        // TODO: before segmented LRU, last-access time would only update
        // every 60 seconds. Currently it doesn't update at all if an item is
        // marked as ACTIVE. I believe this is a bug... in segmented mode
        // there's no reason to avoid bumping la on every access.
        if (!of.no_update && it != NULL) {
            do_item_bump(c, it, hv);
        }
        item_unlock(hv);
    }

    // we count this command as a normal one if we've gotten this far.
    // TODO: for autovivify case, miss never happens. Is this okay?
    if (!failed) {
        pthread_mutex_lock(&c->thread->stats.mutex);
        if (ttl_set) {
            c->thread->stats.touch_cmds++;
            c->thread->stats.slab_stats[ITEM_clsid(it)].touch_hits++;
        } else {
            c->thread->stats.lru_hits[it->slabs_clsid]++;
            c->thread->stats.get_cmds++;
        }
        pthread_mutex_unlock(&c->thread->stats.mutex);

        conn_set_state(c, conn_write);
        c->write_and_go = conn_new_cmd;
    } else {
        pthread_mutex_lock(&c->thread->stats.mutex);
        if (ttl_set) {
            c->thread->stats.touch_cmds++;
            c->thread->stats.touch_misses++;
        } else {
            c->thread->stats.get_misses++;
            c->thread->stats.get_cmds++;
        }
        MEMCACHED_COMMAND_GET(c->sfd, key, nkey, -1, 0);
        pthread_mutex_unlock(&c->thread->stats.mutex);

        // This gets elided in noreply mode.
        out_string(c, "EN");
    }
    return;
error:
    if (it && of.locked) {
        item_unlock(hv);
    }
    out_errstring(c, errstr);
}