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
struct ceph_object_locator {int /*<<< orphan*/ * pool_ns; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ceph_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_oloc_destroy (struct ceph_object_locator*) ; 

void ceph_oloc_copy(struct ceph_object_locator *dest,
		    const struct ceph_object_locator *src)
{
	ceph_oloc_destroy(dest);

	dest->pool = src->pool;
	if (src->pool_ns)
		dest->pool_ns = ceph_get_string(src->pool_ns);
	else
		dest->pool_ns = NULL;
}