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
struct cgroup_subsys_state {int dummy; } ;
struct cgroup_subsys {int /*<<< orphan*/  css_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct cgroup_subsys_state* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 

struct cgroup_subsys_state *css_from_id(int id, struct cgroup_subsys *ss)
{
	WARN_ON_ONCE(!rcu_read_lock_held());
	return idr_find(&ss->css_idr, id);
}