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
 int /*<<< orphan*/ ** sk_THREAD_EVENT_HANDLER_PTR_delete (int /*<<< orphan*/ ,int) ; 
 int sk_THREAD_EVENT_HANDLER_PTR_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** sk_THREAD_EVENT_HANDLER_PTR_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_thread_remove_handlers(THREAD_EVENT_HANDLER **handsin)
{
    GLOBAL_TEVENT_REGISTER *gtr;
    int i;

    gtr = get_global_tevent_register();
    if (gtr == NULL)
        return;
    CRYPTO_THREAD_write_lock(gtr->lock);
    for (i = 0; i < sk_THREAD_EVENT_HANDLER_PTR_num(gtr->skhands); i++) {
        THREAD_EVENT_HANDLER **hands
            = sk_THREAD_EVENT_HANDLER_PTR_value(gtr->skhands, i);

        if (hands == handsin) {
            hands = sk_THREAD_EVENT_HANDLER_PTR_delete(gtr->skhands, i);
            CRYPTO_THREAD_unlock(gtr->lock);
            return;
        }
    }
    CRYPTO_THREAD_unlock(gtr->lock);
    return;
}