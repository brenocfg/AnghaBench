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
struct TYPE_2__ {int /*<<< orphan*/  bdi_node; } ;
struct backing_dev_info {int /*<<< orphan*/  wb_list; TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgwb_bdi_register(struct backing_dev_info *bdi)
{
	list_add_tail_rcu(&bdi->wb.bdi_node, &bdi->wb_list);
}