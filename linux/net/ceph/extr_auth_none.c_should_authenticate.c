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
struct ceph_auth_none_info {int starting; } ;
struct ceph_auth_client {struct ceph_auth_none_info* private; } ;

/* Variables and functions */

__attribute__((used)) static int should_authenticate(struct ceph_auth_client *ac)
{
	struct ceph_auth_none_info *xi = ac->private;

	return xi->starting;
}