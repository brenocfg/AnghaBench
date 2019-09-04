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
struct ceph_auth_client {int dummy; } ;

/* Variables and functions */
 int CEPH_ENTITY_TYPE_AUTH ; 
 int /*<<< orphan*/  invalidate_ticket (struct ceph_auth_client*,int) ; 

__attribute__((used)) static void ceph_x_invalidate_authorizer(struct ceph_auth_client *ac,
					 int peer_type)
{
	/*
	 * We are to invalidate a service ticket in the hopes of
	 * getting a new, hopefully more valid, one.  But, we won't get
	 * it unless our AUTH ticket is good, so invalidate AUTH ticket
	 * as well, just in case.
	 */
	invalidate_ticket(ac, peer_type);
	invalidate_ticket(ac, CEPH_ENTITY_TYPE_AUTH);
}