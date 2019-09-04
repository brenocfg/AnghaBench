#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_23__ {char* value; size_t length; } ;
typedef  TYPE_4__ token_t ;
struct TYPE_24__ {int /*<<< orphan*/  nkey; } ;
typedef  TYPE_5__ item ;
struct TYPE_25__ {TYPE_3__* thread; int /*<<< orphan*/  sfd; } ;
typedef  TYPE_6__ conn ;
struct TYPE_26__ {scalar_t__ detail_enabled; } ;
struct TYPE_21__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  delete_misses; TYPE_1__* slab_stats; } ;
struct TYPE_22__ {TYPE_2__ stats; int /*<<< orphan*/  storage; } ;
struct TYPE_20__ {int /*<<< orphan*/  delete_hits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DONT_UPDATE ; 
 size_t ITEM_clsid (TYPE_5__*) ; 
 int /*<<< orphan*/  ITEM_key (TYPE_5__*) ; 
 size_t KEY_MAX_LENGTH ; 
 int KEY_TOKEN ; 
 int /*<<< orphan*/  MEMCACHED_COMMAND_DELETE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORAGE_delete (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_item_remove (TYPE_5__*) ; 
 int /*<<< orphan*/  do_item_unlink (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* item_get_locked (char*,size_t,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  item_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_string (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_noreply_maybe (TYPE_6__*,TYPE_4__*,size_t const) ; 
 TYPE_7__ settings ; 
 int /*<<< orphan*/  stats_prefix_record_delete (char*,size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void process_delete_command(conn *c, token_t *tokens, const size_t ntokens) {
    char *key;
    size_t nkey;
    item *it;
    uint32_t hv;

    assert(c != NULL);

    if (ntokens > 3) {
        bool hold_is_zero = strcmp(tokens[KEY_TOKEN+1].value, "0") == 0;
        bool sets_noreply = set_noreply_maybe(c, tokens, ntokens);
        bool valid = (ntokens == 4 && (hold_is_zero || sets_noreply))
            || (ntokens == 5 && hold_is_zero && sets_noreply);
        if (!valid) {
            out_string(c, "CLIENT_ERROR bad command line format.  "
                       "Usage: delete <key> [noreply]");
            return;
        }
    }


    key = tokens[KEY_TOKEN].value;
    nkey = tokens[KEY_TOKEN].length;

    if(nkey > KEY_MAX_LENGTH) {
        out_string(c, "CLIENT_ERROR bad command line format");
        return;
    }

    if (settings.detail_enabled) {
        stats_prefix_record_delete(key, nkey);
    }

    it = item_get_locked(key, nkey, c, DONT_UPDATE, &hv);
    if (it) {
        MEMCACHED_COMMAND_DELETE(c->sfd, ITEM_key(it), it->nkey);

        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.slab_stats[ITEM_clsid(it)].delete_hits++;
        pthread_mutex_unlock(&c->thread->stats.mutex);

        do_item_unlink(it, hv);
        STORAGE_delete(c->thread->storage, it);
        do_item_remove(it);      /* release our reference */
        out_string(c, "DELETED");
    } else {
        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.delete_misses++;
        pthread_mutex_unlock(&c->thread->stats.mutex);

        out_string(c, "NOT_FOUND");
    }
    item_unlock(hv);
}