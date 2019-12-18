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
struct path {int dummy; } ;
struct file {int dummy; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ IS_ERR (struct file*) ; 
 size_t OVL_COPY_UP_CHUNK_SIZE ; 
 int O_LARGEFILE ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  SPLICE_F_MOVE ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  current ; 
 size_t do_clone_file_range (struct file*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 long do_splice_direct (struct file*,size_t*,struct file*,size_t*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* ovl_path_open (struct path*,int) ; 
 scalar_t__ signal_pending_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfs_fsync (struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_copy_up_data(struct path *old, struct path *new, loff_t len)
{
	struct file *old_file;
	struct file *new_file;
	loff_t old_pos = 0;
	loff_t new_pos = 0;
	loff_t cloned;
	int error = 0;

	if (len == 0)
		return 0;

	old_file = ovl_path_open(old, O_LARGEFILE | O_RDONLY);
	if (IS_ERR(old_file))
		return PTR_ERR(old_file);

	new_file = ovl_path_open(new, O_LARGEFILE | O_WRONLY);
	if (IS_ERR(new_file)) {
		error = PTR_ERR(new_file);
		goto out_fput;
	}

	/* Try to use clone_file_range to clone up within the same fs */
	cloned = do_clone_file_range(old_file, 0, new_file, 0, len, 0);
	if (cloned == len)
		goto out;
	/* Couldn't clone, so now we try to copy the data */

	/* FIXME: copy up sparse files efficiently */
	while (len) {
		size_t this_len = OVL_COPY_UP_CHUNK_SIZE;
		long bytes;

		if (len < this_len)
			this_len = len;

		if (signal_pending_state(TASK_KILLABLE, current)) {
			error = -EINTR;
			break;
		}

		bytes = do_splice_direct(old_file, &old_pos,
					 new_file, &new_pos,
					 this_len, SPLICE_F_MOVE);
		if (bytes <= 0) {
			error = bytes;
			break;
		}
		WARN_ON(old_pos != new_pos);

		len -= bytes;
	}
out:
	if (!error)
		error = vfs_fsync(new_file, 0);
	fput(new_file);
out_fput:
	fput(old_file);
	return error;
}