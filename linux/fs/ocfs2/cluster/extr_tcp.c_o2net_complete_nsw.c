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
typedef  scalar_t__ u64 ;
struct o2net_status_wait {int dummy; } ;
struct o2net_node {int /*<<< orphan*/  nn_lock; int /*<<< orphan*/  nn_status_idr; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum o2net_system_error { ____Placeholder_o2net_system_error } o2net_system_error ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 struct o2net_status_wait* idr_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  o2net_complete_nsw_locked (struct o2net_node*,struct o2net_status_wait*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2net_complete_nsw(struct o2net_node *nn,
			       struct o2net_status_wait *nsw,
			       u64 id, enum o2net_system_error sys_status,
			       s32 status)
{
	spin_lock(&nn->nn_lock);
	if (nsw == NULL) {
		if (id > INT_MAX)
			goto out;

		nsw = idr_find(&nn->nn_status_idr, id);
		if (nsw == NULL)
			goto out;
	}

	o2net_complete_nsw_locked(nn, nsw, sys_status, status);

out:
	spin_unlock(&nn->nn_lock);
	return;
}