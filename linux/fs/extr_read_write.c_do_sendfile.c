#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_sb; } ;
struct fd {TYPE_2__* file; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_11__ {int f_mode; scalar_t__ f_pos; int f_flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_maxbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  ESPIPE ; 
 int FMODE_PREAD ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 size_t MAX_RW_COUNT ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  READ ; 
 int SPLICE_F_NONBLOCK ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  add_rchar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wchar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  do_splice_direct (TYPE_2__*,scalar_t__*,TYPE_2__*,scalar_t__*,size_t,int) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  file_end_write (TYPE_2__*) ; 
 struct inode* file_inode (TYPE_2__*) ; 
 int /*<<< orphan*/  file_start_write (TYPE_2__*) ; 
 int /*<<< orphan*/  fsnotify_access (TYPE_2__*) ; 
 int /*<<< orphan*/  fsnotify_modify (TYPE_2__*) ; 
 int /*<<< orphan*/  inc_syscr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_syscw (int /*<<< orphan*/ ) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_verify_area (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t do_sendfile(int out_fd, int in_fd, loff_t *ppos,
		  	   size_t count, loff_t max)
{
	struct fd in, out;
	struct inode *in_inode, *out_inode;
	loff_t pos;
	loff_t out_pos;
	ssize_t retval;
	int fl;

	/*
	 * Get input file, and verify that it is ok..
	 */
	retval = -EBADF;
	in = fdget(in_fd);
	if (!in.file)
		goto out;
	if (!(in.file->f_mode & FMODE_READ))
		goto fput_in;
	retval = -ESPIPE;
	if (!ppos) {
		pos = in.file->f_pos;
	} else {
		pos = *ppos;
		if (!(in.file->f_mode & FMODE_PREAD))
			goto fput_in;
	}
	retval = rw_verify_area(READ, in.file, &pos, count);
	if (retval < 0)
		goto fput_in;
	if (count > MAX_RW_COUNT)
		count =  MAX_RW_COUNT;

	/*
	 * Get output file, and verify that it is ok..
	 */
	retval = -EBADF;
	out = fdget(out_fd);
	if (!out.file)
		goto fput_in;
	if (!(out.file->f_mode & FMODE_WRITE))
		goto fput_out;
	in_inode = file_inode(in.file);
	out_inode = file_inode(out.file);
	out_pos = out.file->f_pos;
	retval = rw_verify_area(WRITE, out.file, &out_pos, count);
	if (retval < 0)
		goto fput_out;

	if (!max)
		max = min(in_inode->i_sb->s_maxbytes, out_inode->i_sb->s_maxbytes);

	if (unlikely(pos + count > max)) {
		retval = -EOVERFLOW;
		if (pos >= max)
			goto fput_out;
		count = max - pos;
	}

	fl = 0;
#if 0
	/*
	 * We need to debate whether we can enable this or not. The
	 * man page documents EAGAIN return for the output at least,
	 * and the application is arguably buggy if it doesn't expect
	 * EAGAIN on a non-blocking file descriptor.
	 */
	if (in.file->f_flags & O_NONBLOCK)
		fl = SPLICE_F_NONBLOCK;
#endif
	file_start_write(out.file);
	retval = do_splice_direct(in.file, &pos, out.file, &out_pos, count, fl);
	file_end_write(out.file);

	if (retval > 0) {
		add_rchar(current, retval);
		add_wchar(current, retval);
		fsnotify_access(in.file);
		fsnotify_modify(out.file);
		out.file->f_pos = out_pos;
		if (ppos)
			*ppos = pos;
		else
			in.file->f_pos = pos;
	}

	inc_syscr(current);
	inc_syscw(current);
	if (pos > max)
		retval = -EOVERFLOW;

fput_out:
	fdput(out);
fput_in:
	fdput(in);
out:
	return retval;
}