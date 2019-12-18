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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  flags; int /*<<< orphan*/  inited; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_CTX_FLAG_TERMED ; 
 int /*<<< orphan*/  NN_CTX_FLAG_TERMING ; 
 int NN_MAX_SOCKETS ; 
 int /*<<< orphan*/  nn_close (int) ; 
 int /*<<< orphan*/  nn_condvar_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ self ; 

void nn_term (void)
{
    int i;

    if (!self.inited) {
        return;
    }

    nn_mutex_lock (&self.lock);
    self.flags |= NN_CTX_FLAG_TERMING;
    nn_mutex_unlock (&self.lock);

    /* Make sure we really close resources, this will cause global
       resources to be freed too when the last socket is closed. */
    for (i = 0; i < NN_MAX_SOCKETS; i++) {
        (void) nn_close (i);
    }

    nn_mutex_lock (&self.lock);
    self.flags |= NN_CTX_FLAG_TERMED;
    self.flags &= ~NN_CTX_FLAG_TERMING;
    nn_condvar_broadcast(&self.cond);
    nn_mutex_unlock (&self.lock);
}