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
struct super_block {int cleancache_poolid; } ;

/* Variables and functions */
#define  CLEANCACHE_NO_BACKEND 129 
#define  CLEANCACHE_NO_BACKEND_SHARED 128 
 int /*<<< orphan*/  __cleancache_init_fs (struct super_block*) ; 
 int /*<<< orphan*/  __cleancache_init_shared_fs (struct super_block*) ; 

__attribute__((used)) static void cleancache_register_ops_sb(struct super_block *sb, void *unused)
{
	switch (sb->cleancache_poolid) {
	case CLEANCACHE_NO_BACKEND:
		__cleancache_init_fs(sb);
		break;
	case CLEANCACHE_NO_BACKEND_SHARED:
		__cleancache_init_shared_fs(sb);
		break;
	}
}