#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rs_node; } ;
struct gfs2_inode {struct inode i_inode; scalar_t__ i_rahead; TYPE_1__ i_res; int /*<<< orphan*/ * i_gl; scalar_t__ i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_inode_cachep ; 
 struct gfs2_inode* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct inode *gfs2_alloc_inode(struct super_block *sb)
{
	struct gfs2_inode *ip;

	ip = kmem_cache_alloc(gfs2_inode_cachep, GFP_KERNEL);
	if (!ip)
		return NULL;
	ip->i_flags = 0;
	ip->i_gl = NULL;
	memset(&ip->i_res, 0, sizeof(ip->i_res));
	RB_CLEAR_NODE(&ip->i_res.rs_node);
	ip->i_rahead = 0;
	return &ip->i_inode;
}