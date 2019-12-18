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
struct umh_info {struct file* pipe_from_umh; struct file* pipe_to_umh; } ;
struct subprocess_info {struct umh_info* data; } ;
struct file {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int create_pipe_files (struct file**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int replace_fd (int,struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int umh_pipe_setup(struct subprocess_info *info, struct cred *new)
{
	struct umh_info *umh_info = info->data;
	struct file *from_umh[2];
	struct file *to_umh[2];
	int err;

	/* create pipe to send data to umh */
	err = create_pipe_files(to_umh, 0);
	if (err)
		return err;
	err = replace_fd(0, to_umh[0], 0);
	fput(to_umh[0]);
	if (err < 0) {
		fput(to_umh[1]);
		return err;
	}

	/* create pipe to receive data from umh */
	err = create_pipe_files(from_umh, 0);
	if (err) {
		fput(to_umh[1]);
		replace_fd(0, NULL, 0);
		return err;
	}
	err = replace_fd(1, from_umh[1], 0);
	fput(from_umh[1]);
	if (err < 0) {
		fput(to_umh[1]);
		replace_fd(0, NULL, 0);
		fput(from_umh[0]);
		return err;
	}

	umh_info->pipe_to_umh = to_umh[1];
	umh_info->pipe_from_umh = from_umh[0];
	return 0;
}