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
struct tcp_ulp_ops {int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tcp_ulp_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_ulp_list ; 
 int /*<<< orphan*/  tcp_ulp_list_lock ; 

int tcp_register_ulp(struct tcp_ulp_ops *ulp)
{
	int ret = 0;

	spin_lock(&tcp_ulp_list_lock);
	if (tcp_ulp_find(ulp->name))
		ret = -EEXIST;
	else
		list_add_tail_rcu(&ulp->list, &tcp_ulp_list);
	spin_unlock(&tcp_ulp_list_lock);

	return ret;
}