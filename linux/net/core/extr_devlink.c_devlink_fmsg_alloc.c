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
struct devlink_fmsg {int /*<<< orphan*/  item_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct devlink_fmsg* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct devlink_fmsg *devlink_fmsg_alloc(void)
{
	struct devlink_fmsg *fmsg;

	fmsg = kzalloc(sizeof(*fmsg), GFP_KERNEL);
	if (!fmsg)
		return NULL;

	INIT_LIST_HEAD(&fmsg->item_list);

	return fmsg;
}