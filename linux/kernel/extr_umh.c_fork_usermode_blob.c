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
struct umh_info {int /*<<< orphan*/  list; } ;
struct subprocess_info {int dummy; } ;
struct file {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  UMH_WAIT_EXEC ; 
 int call_usermodehelper_exec (struct subprocess_info*,int /*<<< orphan*/ ) ; 
 struct subprocess_info* call_usermodehelper_setup_file (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umh_info*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 size_t kernel_write (struct file*,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct file* shmem_kernel_file_setup (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umh_clean_and_save_pid ; 
 int /*<<< orphan*/  umh_list ; 
 int /*<<< orphan*/  umh_list_lock ; 
 int /*<<< orphan*/  umh_pipe_setup ; 

int fork_usermode_blob(void *data, size_t len, struct umh_info *info)
{
	struct subprocess_info *sub_info;
	struct file *file;
	ssize_t written;
	loff_t pos = 0;
	int err;

	file = shmem_kernel_file_setup("", len, 0);
	if (IS_ERR(file))
		return PTR_ERR(file);

	written = kernel_write(file, data, len, &pos);
	if (written != len) {
		err = written;
		if (err >= 0)
			err = -ENOMEM;
		goto out;
	}

	err = -ENOMEM;
	sub_info = call_usermodehelper_setup_file(file, umh_pipe_setup,
						  umh_clean_and_save_pid, info);
	if (!sub_info)
		goto out;

	err = call_usermodehelper_exec(sub_info, UMH_WAIT_EXEC);
	if (!err) {
		mutex_lock(&umh_list_lock);
		list_add(&info->list, &umh_list);
		mutex_unlock(&umh_list_lock);
	}
out:
	fput(file);
	return err;
}