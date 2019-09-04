#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  key; } ;
struct cleancache_filekey {TYPE_2__ u; } ;
struct address_space {TYPE_4__* host; } ;
struct TYPE_8__ {TYPE_1__* i_sb; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* invalidate_inode ) (int,struct cleancache_filekey) ;} ;
struct TYPE_5__ {int cleancache_poolid; } ;

/* Variables and functions */
 scalar_t__ cleancache_get_key (TYPE_4__*,struct cleancache_filekey*) ; 
 TYPE_3__* cleancache_ops ; 
 int /*<<< orphan*/  stub1 (int,struct cleancache_filekey) ; 

void __cleancache_invalidate_inode(struct address_space *mapping)
{
	int pool_id = mapping->host->i_sb->cleancache_poolid;
	struct cleancache_filekey key = { .u.key = { 0 } };

	if (!cleancache_ops)
		return;

	if (pool_id >= 0 && cleancache_get_key(mapping->host, &key) >= 0)
		cleancache_ops->invalidate_inode(pool_id, key);
}