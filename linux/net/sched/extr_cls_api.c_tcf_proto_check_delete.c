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
struct tcf_proto {int deleting; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_proto_is_empty (struct tcf_proto*,int) ; 

__attribute__((used)) static bool tcf_proto_check_delete(struct tcf_proto *tp, bool rtnl_held)
{
	spin_lock(&tp->lock);
	if (tcf_proto_is_empty(tp, rtnl_held))
		tp->deleting = true;
	spin_unlock(&tp->lock);
	return tp->deleting;
}