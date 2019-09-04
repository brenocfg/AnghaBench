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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct list_head* next; } ;
struct rio_dev {scalar_t__ comp_tag; TYPE_1__ global_list; } ;
struct list_head {struct list_head* next; } ;

/* Variables and functions */
 struct rio_dev* rio_dev_g (struct list_head*) ; 
 struct list_head rio_devices ; 
 int /*<<< orphan*/  rio_global_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct rio_dev *rio_get_comptag(u32 comp_tag, struct rio_dev *from)
{
	struct list_head *n;
	struct rio_dev *rdev;

	spin_lock(&rio_global_list_lock);
	n = from ? from->global_list.next : rio_devices.next;

	while (n && (n != &rio_devices)) {
		rdev = rio_dev_g(n);
		if (rdev->comp_tag == comp_tag)
			goto exit;
		n = n->next;
	}
	rdev = NULL;
exit:
	spin_unlock(&rio_global_list_lock);
	return rdev;
}