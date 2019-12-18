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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_msgr_slab_exit () ; 
 int /*<<< orphan*/ * ceph_msgr_wq ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zero_page ; 

__attribute__((used)) static void _ceph_msgr_exit(void)
{
	if (ceph_msgr_wq) {
		destroy_workqueue(ceph_msgr_wq);
		ceph_msgr_wq = NULL;
	}

	BUG_ON(zero_page == NULL);
	put_page(zero_page);
	zero_page = NULL;

	ceph_msgr_slab_exit();
}