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
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callback_wq ; 

int nfsd4_create_callback_queue(void)
{
	callback_wq = alloc_ordered_workqueue("nfsd4_callbacks", 0);
	if (!callback_wq)
		return -ENOMEM;
	return 0;
}