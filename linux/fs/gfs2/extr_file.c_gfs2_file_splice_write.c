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
struct pipe_inode_info {int dummy; } ;
struct gfs2_inode {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_size_hint (struct file*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  iter_file_splice_write (struct pipe_inode_info*,struct file*,int /*<<< orphan*/ *,size_t,unsigned int) ; 

__attribute__((used)) static ssize_t gfs2_file_splice_write(struct pipe_inode_info *pipe,
				      struct file *out, loff_t *ppos,
				      size_t len, unsigned int flags)
{
	int error;
	struct gfs2_inode *ip = GFS2_I(out->f_mapping->host);

	error = gfs2_rsqa_alloc(ip);
	if (error)
		return (ssize_t)error;

	gfs2_size_hint(out, *ppos, len);

	return iter_file_splice_write(pipe, out, ppos, len, flags);
}