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
typedef  size_t uint32_t ;
struct jffs2_sb_info {size_t inocache_hashsize; struct jffs2_inode_cache** inocache_list; } ;
struct jffs2_inode_cache {size_t ino; struct jffs2_inode_cache* next; } ;

/* Variables and functions */

struct jffs2_inode_cache *jffs2_get_ino_cache(struct jffs2_sb_info *c, uint32_t ino)
{
	struct jffs2_inode_cache *ret;

	ret = c->inocache_list[ino % c->inocache_hashsize];
	while (ret && ret->ino < ino) {
		ret = ret->next;
	}

	if (ret && ret->ino != ino)
		ret = NULL;

	return ret;
}