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

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  laundry_wq ; 
 int /*<<< orphan*/  nfsd4_destroy_callback_queue () ; 

void
nfs4_state_shutdown(void)
{
	destroy_workqueue(laundry_wq);
	nfsd4_destroy_callback_queue();
}