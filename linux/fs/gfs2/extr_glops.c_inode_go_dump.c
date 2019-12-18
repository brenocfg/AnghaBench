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
struct seq_file {int dummy; } ;
struct TYPE_2__ {unsigned long nrpages; int /*<<< orphan*/  i_pages; } ;
struct inode {int /*<<< orphan*/  i_mode; TYPE_1__ i_data; } ;
struct gfs2_inode {scalar_t__ i_diskflags; int /*<<< orphan*/  i_flags; struct inode i_inode; scalar_t__ i_no_addr; scalar_t__ i_no_formal_ino; } ;
struct gfs2_glock {struct gfs2_inode* gl_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF2DT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_print_dbg (struct seq_file*,char*,char const*,unsigned long long,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned long long,unsigned long) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inode_go_dump(struct seq_file *seq, struct gfs2_glock *gl,
			  const char *fs_id_buf)
{
	struct gfs2_inode *ip = gl->gl_object;
	struct inode *inode = &ip->i_inode;
	unsigned long nrpages;

	if (ip == NULL)
		return;

	xa_lock_irq(&inode->i_data.i_pages);
	nrpages = inode->i_data.nrpages;
	xa_unlock_irq(&inode->i_data.i_pages);

	gfs2_print_dbg(seq, "%s I: n:%llu/%llu t:%u f:0x%02lx d:0x%08x s:%llu "
		       "p:%lu\n", fs_id_buf,
		  (unsigned long long)ip->i_no_formal_ino,
		  (unsigned long long)ip->i_no_addr,
		  IF2DT(ip->i_inode.i_mode), ip->i_flags,
		  (unsigned int)ip->i_diskflags,
		  (unsigned long long)i_size_read(inode), nrpages);
}