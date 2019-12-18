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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  newest; } ;
struct ceph_mon_generic_request {TYPE_1__ u; } ;
struct ceph_mon_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ceph_mon_generic_request*) ; 
 int PTR_ERR (struct ceph_mon_generic_request*) ; 
 struct ceph_mon_generic_request* __ceph_monc_get_version (struct ceph_mon_client*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_generic_request (struct ceph_mon_generic_request*) ; 
 int wait_generic_request (struct ceph_mon_generic_request*) ; 

int ceph_monc_get_version(struct ceph_mon_client *monc, const char *what,
			  u64 *newest)
{
	struct ceph_mon_generic_request *req;
	int ret;

	req = __ceph_monc_get_version(monc, what, NULL, 0);
	if (IS_ERR(req))
		return PTR_ERR(req);

	ret = wait_generic_request(req);
	if (!ret)
		*newest = req->u.newest;

	put_generic_request(req);
	return ret;
}