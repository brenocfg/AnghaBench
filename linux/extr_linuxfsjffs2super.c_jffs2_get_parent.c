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
typedef  int /*<<< orphan*/  uint32_t ;
struct jffs2_inode_info {TYPE_1__* inocache; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  ino; int /*<<< orphan*/  pino_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  JFFS2_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jffs2_inode_info* JFFS2_INODE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *jffs2_get_parent(struct dentry *child)
{
	struct jffs2_inode_info *f;
	uint32_t pino;

	BUG_ON(!d_is_dir(child));

	f = JFFS2_INODE_INFO(d_inode(child));

	pino = f->inocache->pino_nlink;

	JFFS2_DEBUG("Parent of directory ino #%u is #%u\n",
		    f->inocache->ino, pino);

	return d_obtain_alias(jffs2_iget(child->d_sb, pino));
}