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
struct nn_worker_fd {int /*<<< orphan*/  hndl; } ;
struct nn_worker {int /*<<< orphan*/  poller; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_poller_reset_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nn_worker_reset_in (struct nn_worker *self, struct nn_worker_fd *fd)
{
    nn_poller_reset_in (&self->poller, &fd->hndl);
}