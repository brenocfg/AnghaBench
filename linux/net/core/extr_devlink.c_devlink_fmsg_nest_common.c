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
struct devlink_fmsg_item {int attrtype; int /*<<< orphan*/  list; } ;
struct devlink_fmsg {int /*<<< orphan*/  item_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct devlink_fmsg_item* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int devlink_fmsg_nest_common(struct devlink_fmsg *fmsg,
				    int attrtype)
{
	struct devlink_fmsg_item *item;

	item = kzalloc(sizeof(*item), GFP_KERNEL);
	if (!item)
		return -ENOMEM;

	item->attrtype = attrtype;
	list_add_tail(&item->list, &fmsg->item_list);

	return 0;
}