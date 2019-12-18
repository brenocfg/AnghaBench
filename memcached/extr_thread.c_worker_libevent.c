#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ drop_privileges; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; int /*<<< orphan*/ * lru_bump_buf; int /*<<< orphan*/ * l; } ;
typedef  TYPE_1__ LIBEVENT_THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  drop_worker_privileges () ; 
 int /*<<< orphan*/  event_base_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * item_lru_bump_buf_create () ; 
 int /*<<< orphan*/ * logger_create () ; 
 int /*<<< orphan*/  register_thread_initialized () ; 
 TYPE_2__ settings ; 

__attribute__((used)) static void *worker_libevent(void *arg) {
    LIBEVENT_THREAD *me = arg;

    /* Any per-thread setup can happen here; memcached_thread_init() will block until
     * all threads have finished initializing.
     */
    me->l = logger_create();
    me->lru_bump_buf = item_lru_bump_buf_create();
    if (me->l == NULL || me->lru_bump_buf == NULL) {
        abort();
    }

    if (settings.drop_privileges) {
        drop_worker_privileges();
    }

    register_thread_initialized();

    event_base_loop(me->base, 0);

    // same mechanism used to watch for all threads exiting.
    register_thread_initialized();

    event_base_free(me->base);
    return NULL;
}