#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cnid; scalar_t__ fork_type; scalar_t__ start_block; } ;
struct TYPE_6__ {TYPE_1__ ext; } ;
typedef  TYPE_2__ hfsplus_btree_key ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (scalar_t__) ; 

int hfsplus_ext_cmp_key(const hfsplus_btree_key *k1,
			const hfsplus_btree_key *k2)
{
	__be32 k1id, k2id;
	__be32 k1s, k2s;

	k1id = k1->ext.cnid;
	k2id = k2->ext.cnid;
	if (k1id != k2id)
		return be32_to_cpu(k1id) < be32_to_cpu(k2id) ? -1 : 1;

	if (k1->ext.fork_type != k2->ext.fork_type)
		return k1->ext.fork_type < k2->ext.fork_type ? -1 : 1;

	k1s = k1->ext.start_block;
	k2s = k2->ext.start_block;
	if (k1s == k2s)
		return 0;
	return be32_to_cpu(k1s) < be32_to_cpu(k2s) ? -1 : 1;
}