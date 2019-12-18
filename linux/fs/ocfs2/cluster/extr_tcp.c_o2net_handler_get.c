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
typedef  int /*<<< orphan*/  u32 ;
struct o2net_msg_handler {int /*<<< orphan*/  nh_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2net_handler_lock ; 
 struct o2net_msg_handler* o2net_handler_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct o2net_msg_handler *o2net_handler_get(u32 msg_type, u32 key)
{
	struct o2net_msg_handler *nmh;

	read_lock(&o2net_handler_lock);
	nmh = o2net_handler_tree_lookup(msg_type, key, NULL, NULL);
	if (nmh)
		kref_get(&nmh->nh_kref);
	read_unlock(&o2net_handler_lock);

	return nmh;
}