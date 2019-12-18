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
struct ceph_object_locator {int /*<<< orphan*/  pool_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_put_string (int /*<<< orphan*/ ) ; 

void ceph_oloc_destroy(struct ceph_object_locator *oloc)
{
	ceph_put_string(oloc->pool_ns);
}