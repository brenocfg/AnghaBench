#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct backing_dev_info {TYPE_1__* wb_congested; int /*<<< orphan*/  wb; } ;
struct TYPE_3__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wb_congested_put (TYPE_1__*) ; 
 int wb_init (int /*<<< orphan*/ *,struct backing_dev_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cgwb_bdi_init(struct backing_dev_info *bdi)
{
	int err;

	bdi->wb_congested = kzalloc(sizeof(*bdi->wb_congested), GFP_KERNEL);
	if (!bdi->wb_congested)
		return -ENOMEM;

	refcount_set(&bdi->wb_congested->refcnt, 1);

	err = wb_init(&bdi->wb, bdi, 1, GFP_KERNEL);
	if (err) {
		wb_congested_put(bdi->wb_congested);
		return err;
	}
	return 0;
}