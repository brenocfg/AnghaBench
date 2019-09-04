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
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_debugfs_exit () ; 
 int /*<<< orphan*/  o2net_hand ; 
 int /*<<< orphan*/  o2net_keep_req ; 
 int /*<<< orphan*/  o2net_keep_resp ; 
 int /*<<< orphan*/  o2quo_exit () ; 

void o2net_exit(void)
{
	o2quo_exit();
	kfree(o2net_hand);
	kfree(o2net_keep_req);
	kfree(o2net_keep_resp);
	o2net_debugfs_exit();
}