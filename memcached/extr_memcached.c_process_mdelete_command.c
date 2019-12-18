#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_25__ {size_t length; char* value; } ;
typedef  TYPE_4__ token_t ;
struct _meta_flags {scalar_t__ set_stale; int /*<<< orphan*/  no_reply; int /*<<< orphan*/  member_0; } ;
struct TYPE_26__ {int /*<<< orphan*/  it_flags; int /*<<< orphan*/  exptime; int /*<<< orphan*/  nkey; } ;
typedef  TYPE_5__ item ;
struct TYPE_27__ {char* wbuf; int wbytes; TYPE_3__* thread; int /*<<< orphan*/  sfd; int /*<<< orphan*/  noreply; } ;
typedef  TYPE_6__ conn ;
struct TYPE_28__ {scalar_t__ use_cas; } ;
struct TYPE_23__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  delete_misses; TYPE_1__* slab_stats; } ;
struct TYPE_24__ {TYPE_2__ stats; int /*<<< orphan*/  storage; } ;
struct TYPE_22__ {int /*<<< orphan*/  delete_hits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_NOREPLY ; 
 int /*<<< orphan*/  DISABLE_NOREPLY ; 
 int /*<<< orphan*/  DONT_UPDATE ; 
 int /*<<< orphan*/  ITEM_STALE ; 
 int /*<<< orphan*/  ITEM_TOKEN_SENT ; 
 size_t ITEM_clsid (TYPE_5__*) ; 
 scalar_t__ ITEM_get_cas (TYPE_5__*) ; 
 int /*<<< orphan*/  ITEM_key (TYPE_5__*) ; 
 int /*<<< orphan*/  ITEM_set_cas (TYPE_5__*,int /*<<< orphan*/ ) ; 
 size_t KEY_MAX_LENGTH ; 
 size_t KEY_TOKEN ; 
 int /*<<< orphan*/  MEMCACHED_COMMAND_DELETE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MFLAG_MAX_OPAQUE_LENGTH ; 
 int MFLAG_MAX_OPT_LENGTH ; 
 int /*<<< orphan*/  STORAGE_delete (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int _meta_flag_preparse (char*,int,struct _meta_flags*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_item_remove (TYPE_5__*) ; 
 int /*<<< orphan*/  do_item_unlink (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cas_id () ; 
 TYPE_5__* item_get_locked (char*,size_t,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  item_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  out_errstring (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  out_mstring (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_string (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strtoul (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_strtoull (char*,scalar_t__*) ; 
 TYPE_7__ settings ; 

__attribute__((used)) static void process_mdelete_command(conn *c, token_t *tokens, const size_t ntokens) {
    char *key;
    size_t nkey;
    uint32_t exptime_int = 0;
    uint64_t req_cas_id = 0;
    char *p;
    int rtokens;
    item *it = NULL;
    char *opts;
    int olen, i;
    uint32_t hv;
    struct _meta_flags of = {0}; // option bitflags.
    char *errstr = "CLIENT_ERROR bad command line format";

    assert(c != NULL);

    // TODO: most of this is identical to mget.
    if (tokens[KEY_TOKEN].length > KEY_MAX_LENGTH) {
        out_string(c, "CLIENT_ERROR bad command line format");
        return;
    }

    key = tokens[KEY_TOKEN].value;
    nkey = tokens[KEY_TOKEN].length;

    rtokens = 3; // cmd, key, final.

    // rtokens == 0 acts like a normal immediate delete
    if (ntokens == 3) {
        opts = "";
        olen = 0;
    } else {
        opts = tokens[KEY_TOKEN + 1].value;
        olen = tokens[KEY_TOKEN + 1].length;
        rtokens++;
    }

    if (olen > MFLAG_MAX_OPT_LENGTH) {
        out_string(c, "CLIENT_ERROR options flags too long");
        return;
    }

    // copy opts before munging them.
    // first two chars is status code.
    p = c->wbuf + 3;
    memcpy(p, opts, olen);
    p += olen;

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

    assert(c != NULL);
    bool new_ttl = false;
    for (i = 0; i < olen; i++) {
        switch (opts[i]) {
            case 'C':
                if (!safe_strtoull(tokens[rtokens].value, &req_cas_id)) {
                    goto error;
                }
                rtokens++;
                break;
            case 'T':
                if (!safe_strtoul(tokens[rtokens].value, &exptime_int)) {
                    goto error;
                }
                new_ttl = true;
                rtokens++;
                break;
            // TODO: macro perhaps?
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
                memcpy(p+1, key, nkey);
                p += nkey + 1;
                rtokens++;
                break;
        }
    }

    it = item_get_locked(key, nkey, c, DONT_UPDATE, &hv);
    if (it) {
        MEMCACHED_COMMAND_DELETE(c->sfd, ITEM_key(it), it->nkey);

        // allow only deleting/marking if a CAS value matches.
        if (req_cas_id != 0 && ITEM_get_cas(it) != req_cas_id) {
            pthread_mutex_lock(&c->thread->stats.mutex);
            c->thread->stats.delete_misses++;
            pthread_mutex_unlock(&c->thread->stats.mutex);

            // Need to ensure client gets this response.
            memcpy(c->wbuf, "EX ", 3);
            c->wbytes = p - c->wbuf;
            out_mstring(c, DISABLE_NOREPLY);
            goto cleanup;
        }

        // If we're to set this item as stale, we don't actually want to
        // delete it. We mark the stale bit, bump CAS, and update exptime if
        // we were supplied a new TTL.
        if (of.set_stale) {
            if (new_ttl) {
                it->exptime = realtime(exptime_int);
            }
            it->it_flags |= ITEM_STALE;
            // Also need to remove TOKEN_SENT, so next client can win.
            it->it_flags &= ~ITEM_TOKEN_SENT;

            ITEM_set_cas(it, (settings.use_cas) ? get_cas_id() : 0);

            memcpy(c->wbuf, "DE ", 3);
            // TODO: just use two diff funcs? :|
            // also, take len for arg?
            c->wbytes = p - c->wbuf;
            out_mstring(c, ALLOW_NOREPLY);
        } else {
            pthread_mutex_lock(&c->thread->stats.mutex);
            c->thread->stats.slab_stats[ITEM_clsid(it)].delete_hits++;
            pthread_mutex_unlock(&c->thread->stats.mutex);

            do_item_unlink(it, hv);
            STORAGE_delete(c->thread->storage, it);
            memcpy(c->wbuf, "DE ", 3);
            c->wbytes = p - c->wbuf;
            out_mstring(c, ALLOW_NOREPLY);
        }
        goto cleanup;
    } else {
        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.delete_misses++;
        pthread_mutex_unlock(&c->thread->stats.mutex);

        memcpy(c->wbuf, "NF ", 3);
        c->wbytes = p - c->wbuf;
        out_mstring(c, ALLOW_NOREPLY);
        goto cleanup;
    }
cleanup:
    if (it) {
        do_item_remove(it);
    }
    // Item is always returned locked, even if missing.
    item_unlock(hv);
    return;
error:
    out_errstring(c, errstr);
}