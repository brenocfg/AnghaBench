#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t length; char* value; } ;
typedef  TYPE_4__ token_t ;
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_16__ {TYPE_3__* thread; } ;
typedef  TYPE_5__ conn ;
struct TYPE_13__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  touch_misses; int /*<<< orphan*/  touch_cmds; TYPE_1__* slab_stats; } ;
struct TYPE_14__ {TYPE_2__ stats; } ;
struct TYPE_12__ {int /*<<< orphan*/  touch_hits; } ;

/* Variables and functions */
 size_t ITEM_clsid (int /*<<< orphan*/ *) ; 
 size_t KEY_MAX_LENGTH ; 
 size_t KEY_TOKEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * item_touch (char*,size_t,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  out_string (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strtol (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_noreply_maybe (TYPE_5__*,TYPE_4__*,size_t const) ; 

__attribute__((used)) static void process_touch_command(conn *c, token_t *tokens, const size_t ntokens) {
    char *key;
    size_t nkey;
    int32_t exptime_int = 0;
    item *it;

    assert(c != NULL);

    set_noreply_maybe(c, tokens, ntokens);

    if (tokens[KEY_TOKEN].length > KEY_MAX_LENGTH) {
        out_string(c, "CLIENT_ERROR bad command line format");
        return;
    }

    key = tokens[KEY_TOKEN].value;
    nkey = tokens[KEY_TOKEN].length;

    if (!safe_strtol(tokens[2].value, &exptime_int)) {
        out_string(c, "CLIENT_ERROR invalid exptime argument");
        return;
    }

    it = item_touch(key, nkey, realtime(exptime_int), c);
    if (it) {
        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.touch_cmds++;
        c->thread->stats.slab_stats[ITEM_clsid(it)].touch_hits++;
        pthread_mutex_unlock(&c->thread->stats.mutex);

        out_string(c, "TOUCHED");
        item_remove(it);
    } else {
        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.touch_cmds++;
        c->thread->stats.touch_misses++;
        pthread_mutex_unlock(&c->thread->stats.mutex);

        out_string(c, "NOT_FOUND");
    }
}