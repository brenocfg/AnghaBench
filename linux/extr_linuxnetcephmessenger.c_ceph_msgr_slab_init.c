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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * KMEM_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_msg ; 
 int /*<<< orphan*/ * ceph_msg_cache ; 
 int /*<<< orphan*/  ceph_msg_data ; 
 int /*<<< orphan*/ * ceph_msg_data_cache ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceph_msgr_slab_init(void)
{
	BUG_ON(ceph_msg_cache);
	ceph_msg_cache = KMEM_CACHE(ceph_msg, 0);
	if (!ceph_msg_cache)
		return -ENOMEM;

	BUG_ON(ceph_msg_data_cache);
	ceph_msg_data_cache = KMEM_CACHE(ceph_msg_data, 0);
	if (ceph_msg_data_cache)
		return 0;

	kmem_cache_destroy(ceph_msg_cache);
	ceph_msg_cache = NULL;

	return -ENOMEM;
}