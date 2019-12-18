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
struct ceph_msg {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct ceph_msg* ceph_msg_new2 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct ceph_msg *ceph_msg_new(int type, int front_len, gfp_t flags,
			      bool can_fail)
{
	return ceph_msg_new2(type, front_len, 0, flags, can_fail);
}