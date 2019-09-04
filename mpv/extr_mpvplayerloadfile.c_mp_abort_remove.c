#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mp_abort_entry {int /*<<< orphan*/  cancel; } ;
struct MPContext {int num_abort_list; int /*<<< orphan*/  abort_lock; struct mp_abort_entry** abort_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct mp_abort_entry**,int,int) ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_abort_remove(struct MPContext *mpctx, struct mp_abort_entry *abort)
{
    pthread_mutex_lock(&mpctx->abort_lock);
    for (int n = 0; n < mpctx->num_abort_list; n++) {
        if (mpctx->abort_list[n] == abort) {
            MP_TARRAY_REMOVE_AT(mpctx->abort_list, mpctx->num_abort_list, n);
            TA_FREEP(&abort->cancel);
            abort = NULL; // it's not free'd, just clear for the assert below
            break;
        }
    }
    assert(!abort); // should have been in the list
    pthread_mutex_unlock(&mpctx->abort_lock);
}