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
typedef  int /*<<< orphan*/  u64 ;
struct ceph_mon_generic_request {int dummy; } ;
struct ceph_mon_client {int dummy; } ;
typedef  int /*<<< orphan*/  ceph_monc_callback_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ceph_mon_generic_request*) ; 
 int PTR_ERR (struct ceph_mon_generic_request*) ; 
 struct ceph_mon_generic_request* __ceph_monc_get_version (struct ceph_mon_client*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_generic_request (struct ceph_mon_generic_request*) ; 

int ceph_monc_get_version_async(struct ceph_mon_client *monc, const char *what,
				ceph_monc_callback_t cb, u64 private_data)
{
	struct ceph_mon_generic_request *req;

	req = __ceph_monc_get_version(monc, what, cb, private_data);
	if (IS_ERR(req))
		return PTR_ERR(req);

	put_generic_request(req);
	return 0;
}