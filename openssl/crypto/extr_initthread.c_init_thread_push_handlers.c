#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  skhands; } ;
typedef  int /*<<< orphan*/  THREAD_EVENT_HANDLER ;
typedef  TYPE_1__ GLOBAL_TEVENT_REGISTER ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_global_tevent_register () ; 
 scalar_t__ sk_THREAD_EVENT_HANDLER_PTR_push (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int init_thread_push_handlers(THREAD_EVENT_HANDLER **hands)
{
    int ret;
    GLOBAL_TEVENT_REGISTER *gtr;

    gtr = get_global_tevent_register();
    if (gtr == NULL)
        return 0;

    CRYPTO_THREAD_write_lock(gtr->lock);
    ret = (sk_THREAD_EVENT_HANDLER_PTR_push(gtr->skhands, hands) != 0);
    CRYPTO_THREAD_unlock(gtr->lock);

    return ret;
}