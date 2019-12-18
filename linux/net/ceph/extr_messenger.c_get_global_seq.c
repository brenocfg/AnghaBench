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
typedef  scalar_t__ u32 ;
struct ceph_messenger {scalar_t__ global_seq; int /*<<< orphan*/  global_seq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 get_global_seq(struct ceph_messenger *msgr, u32 gt)
{
	u32 ret;

	spin_lock(&msgr->global_seq_lock);
	if (msgr->global_seq < gt)
		msgr->global_seq = gt;
	ret = ++msgr->global_seq;
	spin_unlock(&msgr->global_seq_lock);
	return ret;
}