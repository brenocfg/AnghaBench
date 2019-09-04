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
struct ceph_mon_generic_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __finish_generic_request (struct ceph_mon_generic_request*) ; 
 int /*<<< orphan*/  put_generic_request (struct ceph_mon_generic_request*) ; 

__attribute__((used)) static void finish_generic_request(struct ceph_mon_generic_request *req)
{
	__finish_generic_request(req);
	put_generic_request(req);
}