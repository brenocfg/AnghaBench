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
 int ENOMEM ; 
 int /*<<< orphan*/  WQ_UNBOUND ; 
 int /*<<< orphan*/ * alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * laundry_wq ; 
 int nfsd4_create_callback_queue () ; 
 int /*<<< orphan*/  set_max_delegations () ; 

int
nfs4_state_start(void)
{
	int ret;

	laundry_wq = alloc_workqueue("%s", WQ_UNBOUND, 0, "nfsd4");
	if (laundry_wq == NULL) {
		ret = -ENOMEM;
		goto out;
	}
	ret = nfsd4_create_callback_queue();
	if (ret)
		goto out_free_laundry;

	set_max_delegations();
	return 0;

out_free_laundry:
	destroy_workqueue(laundry_wq);
out:
	return ret;
}