#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int NN_CTX_FLAG_TERMED ; 
 int NN_CTX_FLAG_TERMING ; 
 int /*<<< orphan*/  nn_condvar_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_do_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_lib_init ; 
 int /*<<< orphan*/  nn_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  once ; 
 TYPE_1__ self ; 

void nn_init (void)
{
    nn_do_once (&once, nn_lib_init);

    nn_mutex_lock (&self.lock);
    /*  Wait for any in progress term to complete. */
    while (self.flags & NN_CTX_FLAG_TERMING) {
        nn_condvar_wait (&self.cond, &self.lock, -1);
    }
    self.flags &= ~NN_CTX_FLAG_TERMED;
    nn_mutex_unlock (&self.lock);
}