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
struct backing_dev_info {int max_ratio; int /*<<< orphan*/  wb_waitq; int /*<<< orphan*/  wb_list; int /*<<< orphan*/  bdi_list; int /*<<< orphan*/  max_prop_frac; scalar_t__ min_ratio; int /*<<< orphan*/  refcnt; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPROP_FRAC_BASE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int cgwb_bdi_init (struct backing_dev_info*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bdi_init(struct backing_dev_info *bdi)
{
	int ret;

	bdi->dev = NULL;

	kref_init(&bdi->refcnt);
	bdi->min_ratio = 0;
	bdi->max_ratio = 100;
	bdi->max_prop_frac = FPROP_FRAC_BASE;
	INIT_LIST_HEAD(&bdi->bdi_list);
	INIT_LIST_HEAD(&bdi->wb_list);
	init_waitqueue_head(&bdi->wb_waitq);

	ret = cgwb_bdi_init(bdi);

	return ret;
}