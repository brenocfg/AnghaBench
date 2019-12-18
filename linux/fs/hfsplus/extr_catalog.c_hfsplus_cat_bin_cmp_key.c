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
struct TYPE_5__ {scalar_t__ parent; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ cat; } ;
typedef  TYPE_2__ hfsplus_btree_key ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (scalar_t__) ; 
 int hfsplus_strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int hfsplus_cat_bin_cmp_key(const hfsplus_btree_key *k1,
			    const hfsplus_btree_key *k2)
{
	__be32 k1p, k2p;

	k1p = k1->cat.parent;
	k2p = k2->cat.parent;
	if (k1p != k2p)
		return be32_to_cpu(k1p) < be32_to_cpu(k2p) ? -1 : 1;

	return hfsplus_strcmp(&k1->cat.name, &k2->cat.name);
}