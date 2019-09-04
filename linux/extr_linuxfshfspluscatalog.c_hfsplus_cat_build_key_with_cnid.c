#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct TYPE_5__ {scalar_t__ length; } ;
struct TYPE_6__ {TYPE_1__ name; int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  key_len; TYPE_2__ cat; } ;
typedef  TYPE_3__ hfsplus_btree_key ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

void hfsplus_cat_build_key_with_cnid(struct super_block *sb,
			hfsplus_btree_key *key, u32 parent)
{
	key->cat.parent = cpu_to_be32(parent);
	key->cat.name.length = 0;
	key->key_len = cpu_to_be16(6);
}