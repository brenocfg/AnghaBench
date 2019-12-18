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
struct ctl_table_set {int (* is_seen ) (struct ctl_table_set*) ;} ;
struct ctl_table_header {scalar_t__ unregistering; struct ctl_table_set* set; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ctl_table_set*) ; 
 int /*<<< orphan*/  sysctl_lock ; 

__attribute__((used)) static int sysctl_is_seen(struct ctl_table_header *p)
{
	struct ctl_table_set *set = p->set;
	int res;
	spin_lock(&sysctl_lock);
	if (p->unregistering)
		res = 0;
	else if (!set->is_seen)
		res = 1;
	else
		res = set->is_seen(set);
	spin_unlock(&sysctl_lock);
	return res;
}