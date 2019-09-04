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
typedef  int /*<<< orphan*/  u32 ;
struct crush_bucket_tree {int num_nodes; int /*<<< orphan*/ * node_weights; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  bad ; 
 int /*<<< orphan*/  ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_8_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,void*,void*) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crush_decode_tree_bucket(void **p, void *end,
				    struct crush_bucket_tree *b)
{
	int j;
	dout("crush_decode_tree_bucket %p to %p\n", *p, end);
	ceph_decode_8_safe(p, end, b->num_nodes, bad);
	b->node_weights = kcalloc(b->num_nodes, sizeof(u32), GFP_NOFS);
	if (b->node_weights == NULL)
		return -ENOMEM;
	ceph_decode_need(p, end, b->num_nodes * sizeof(u32), bad);
	for (j = 0; j < b->num_nodes; j++)
		b->node_weights[j] = ceph_decode_32(p);
	return 0;
bad:
	return -EINVAL;
}