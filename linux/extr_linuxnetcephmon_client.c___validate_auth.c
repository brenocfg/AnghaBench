#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ceph_mon_client {TYPE_2__* m_auth; int /*<<< orphan*/  auth; scalar_t__ pending_auth; } ;
struct TYPE_3__ {int /*<<< orphan*/  iov_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  front_alloc_len; TYPE_1__ front; } ;

/* Variables and functions */
 int /*<<< orphan*/  __send_prepared_auth_request (struct ceph_mon_client*,int) ; 
 int ceph_build_auth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __validate_auth(struct ceph_mon_client *monc)
{
	int ret;

	if (monc->pending_auth)
		return 0;

	ret = ceph_build_auth(monc->auth, monc->m_auth->front.iov_base,
			      monc->m_auth->front_alloc_len);
	if (ret <= 0)
		return ret; /* either an error, or no need to authenticate */
	__send_prepared_auth_request(monc, ret);
	return 0;
}