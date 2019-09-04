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
struct ceph_msg_data {scalar_t__ type; int /*<<< orphan*/  pagelist; int /*<<< orphan*/  links; } ;

/* Variables and functions */
 scalar_t__ CEPH_MSG_DATA_PAGELIST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_msg_data_cache ; 
 int /*<<< orphan*/  ceph_pagelist_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ceph_msg_data*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ceph_msg_data_destroy(struct ceph_msg_data *data)
{
	if (!data)
		return;

	WARN_ON(!list_empty(&data->links));
	if (data->type == CEPH_MSG_DATA_PAGELIST)
		ceph_pagelist_release(data->pagelist);
	kmem_cache_free(ceph_msg_data_cache, data);
}