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
struct inode {scalar_t__ i_size; TYPE_1__* i_sb; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ s_maxbytes; } ;

/* Variables and functions */
 int EFBIG ; 
 int ETXTBSY ; 
 scalar_t__ IS_SWAPFILE (struct inode const*) ; 
 int /*<<< orphan*/  RLIMIT_FSIZE ; 
 unsigned long RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 int /*<<< orphan*/  current ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int inode_newsize_ok(const struct inode *inode, loff_t offset)
{
	if (inode->i_size < offset) {
		unsigned long limit;

		limit = rlimit(RLIMIT_FSIZE);
		if (limit != RLIM_INFINITY && offset > limit)
			goto out_sig;
		if (offset > inode->i_sb->s_maxbytes)
			goto out_big;
	} else {
		/*
		 * truncation of in-use swapfiles is disallowed - it would
		 * cause subsequent swapout to scribble on the now-freed
		 * blocks.
		 */
		if (IS_SWAPFILE(inode))
			return -ETXTBSY;
	}

	return 0;
out_sig:
	send_sig(SIGXFSZ, current, 0);
out_big:
	return -EFBIG;
}