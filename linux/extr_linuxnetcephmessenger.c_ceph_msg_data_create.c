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
struct ceph_msg_data {int type; int /*<<< orphan*/  links; } ;
typedef  enum ceph_msg_data_type { ____Placeholder_ceph_msg_data_type } ceph_msg_data_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_msg_data_cache ; 
 int /*<<< orphan*/  ceph_msg_data_type_valid (int) ; 
 struct ceph_msg_data* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ceph_msg_data *ceph_msg_data_create(enum ceph_msg_data_type type)
{
	struct ceph_msg_data *data;

	if (WARN_ON(!ceph_msg_data_type_valid(type)))
		return NULL;

	data = kmem_cache_zalloc(ceph_msg_data_cache, GFP_NOFS);
	if (!data)
		return NULL;

	data->type = type;
	INIT_LIST_HEAD(&data->links);

	return data;
}