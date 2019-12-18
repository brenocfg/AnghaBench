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
struct jffs2_raw_node_ref {struct jffs2_raw_node_ref* next_in_ino; } ;
struct jffs2_inode_cache {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct jffs2_inode_cache *jffs2_raw_ref_to_ic(struct jffs2_raw_node_ref *raw)
{
	while(raw->next_in_ino)
		raw = raw->next_in_ino;

	/* NB. This can be a jffs2_xattr_datum or jffs2_xattr_ref and
	   not actually a jffs2_inode_cache. Check ->class */
	return ((struct jffs2_inode_cache *)raw);
}