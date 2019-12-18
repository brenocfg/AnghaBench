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
#define  CEPH_AUTH_CEPHX 129 
#define  CEPH_AUTH_NONE 128 
 int ENOENT ; 
 int ceph_auth_none_init (struct ceph_auth_client*) ; 
 int ceph_x_init (struct ceph_auth_client*) ; 

__attribute__((used)) static int ceph_auth_init_protocol(struct ceph_auth_client *ac, int protocol)
{
	switch (protocol) {
	case CEPH_AUTH_NONE:
		return ceph_auth_none_init(ac);
	case CEPH_AUTH_CEPHX:
		return ceph_x_init(ac);
	default:
		return -ENOENT;
	}
}