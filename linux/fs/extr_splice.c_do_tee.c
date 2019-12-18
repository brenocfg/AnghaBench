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
struct pipe_inode_info {int dummy; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int O_NONBLOCK ; 
 unsigned int SPLICE_F_NONBLOCK ; 
 struct pipe_inode_info* get_pipe_info (struct file*) ; 
 int ipipe_prep (struct pipe_inode_info*,unsigned int) ; 
 int link_pipe (struct pipe_inode_info*,struct pipe_inode_info*,size_t,unsigned int) ; 
 int opipe_prep (struct pipe_inode_info*,unsigned int) ; 

__attribute__((used)) static long do_tee(struct file *in, struct file *out, size_t len,
		   unsigned int flags)
{
	struct pipe_inode_info *ipipe = get_pipe_info(in);
	struct pipe_inode_info *opipe = get_pipe_info(out);
	int ret = -EINVAL;

	/*
	 * Duplicate the contents of ipipe to opipe without actually
	 * copying the data.
	 */
	if (ipipe && opipe && ipipe != opipe) {
		if ((in->f_flags | out->f_flags) & O_NONBLOCK)
			flags |= SPLICE_F_NONBLOCK;

		/*
		 * Keep going, unless we encounter an error. The ipipe/opipe
		 * ordering doesn't really matter.
		 */
		ret = ipipe_prep(ipipe, flags);
		if (!ret) {
			ret = opipe_prep(opipe, flags);
			if (!ret)
				ret = link_pipe(ipipe, opipe, len, flags);
		}
	}

	return ret;
}