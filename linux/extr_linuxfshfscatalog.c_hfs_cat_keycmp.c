#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ ParID; TYPE_1__ CName; } ;
struct TYPE_8__ {TYPE_2__ cat; } ;
typedef  TYPE_3__ btree_key ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (scalar_t__) ; 
 int hfs_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hfs_cat_keycmp(const btree_key *key1, const btree_key *key2)
{
	__be32 k1p, k2p;

	k1p = key1->cat.ParID;
	k2p = key2->cat.ParID;

	if (k1p != k2p)
		return be32_to_cpu(k1p) < be32_to_cpu(k2p) ? -1 : 1;

	return hfs_strcmp(key1->cat.CName.name, key1->cat.CName.len,
			  key2->cat.CName.name, key2->cat.CName.len);
}