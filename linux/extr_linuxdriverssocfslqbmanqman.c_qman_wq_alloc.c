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
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qm_portal_wq ; 

int qman_wq_alloc(void)
{
	qm_portal_wq = alloc_workqueue("qman_portal_wq", 0, 1);
	if (!qm_portal_wq)
		return -ENOMEM;
	return 0;
}