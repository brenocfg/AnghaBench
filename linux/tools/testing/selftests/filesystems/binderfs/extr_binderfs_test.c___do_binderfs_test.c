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
struct binderfs_device {int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  name; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  member_0; } ;
struct binder_version {int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  name; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_CTL_ADD ; 
 int /*<<< orphan*/  BINDER_VERSION ; 
 int EEXIST ; 
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  MNT_DETACH ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  change_to_mountns () ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct binderfs_device*) ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,...) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int /*<<< orphan*/  ksft_inc_pass_cnt () ; 
 int /*<<< orphan*/  ksft_inc_xfail_cnt () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mkdir (char*,int) ; 
 int mount (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  rmdir_protect_errno (char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int umount2 (char*,int /*<<< orphan*/ ) ; 
 int unlink (char*) ; 

__attribute__((used)) static void __do_binderfs_test(void)
{
	int fd, ret, saved_errno;
	size_t len;
	ssize_t wret;
	bool keep = false;
	struct binderfs_device device = { 0 };
	struct binder_version version = { 0 };

	change_to_mountns();

	ret = mkdir("/dev/binderfs", 0755);
	if (ret < 0) {
		if (errno != EEXIST)
			ksft_exit_fail_msg(
				"%s - Failed to create binderfs mountpoint\n",
				strerror(errno));

		keep = true;
	}

	ret = mount(NULL, "/dev/binderfs", "binder", 0, 0);
	if (ret < 0) {
		if (errno != ENODEV)
			ksft_exit_fail_msg("%s - Failed to mount binderfs\n",
					   strerror(errno));

		keep ? : rmdir_protect_errno("/dev/binderfs");
		ksft_exit_skip(
			"The Android binderfs filesystem is not available\n");
	}

	/* binderfs mount test passed */
	ksft_inc_pass_cnt();

	memcpy(device.name, "my-binder", strlen("my-binder"));

	fd = open("/dev/binderfs/binder-control", O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		ksft_exit_fail_msg(
			"%s - Failed to open binder-control device\n",
			strerror(errno));

	ret = ioctl(fd, BINDER_CTL_ADD, &device);
	saved_errno = errno;
	close(fd);
	errno = saved_errno;
	if (ret < 0) {
		keep ? : rmdir_protect_errno("/dev/binderfs");
		ksft_exit_fail_msg(
			"%s - Failed to allocate new binder device\n",
			strerror(errno));
	}

	ksft_print_msg(
		"Allocated new binder device with major %d, minor %d, and name %s\n",
		device.major, device.minor, device.name);

	/* binder device allocation test passed */
	ksft_inc_pass_cnt();

	fd = open("/dev/binderfs/my-binder", O_CLOEXEC | O_RDONLY);
	if (fd < 0) {
		keep ? : rmdir_protect_errno("/dev/binderfs");
		ksft_exit_fail_msg("%s - Failed to open my-binder device\n",
				   strerror(errno));
	}

	ret = ioctl(fd, BINDER_VERSION, &version);
	saved_errno = errno;
	close(fd);
	errno = saved_errno;
	if (ret < 0) {
		keep ? : rmdir_protect_errno("/dev/binderfs");
		ksft_exit_fail_msg(
			"%s - Failed to open perform BINDER_VERSION request\n",
			strerror(errno));
	}

	ksft_print_msg("Detected binder version: %d\n",
		       version.protocol_version);

	/* binder transaction with binderfs binder device passed */
	ksft_inc_pass_cnt();

	ret = unlink("/dev/binderfs/my-binder");
	if (ret < 0) {
		keep ? : rmdir_protect_errno("/dev/binderfs");
		ksft_exit_fail_msg("%s - Failed to delete binder device\n",
				   strerror(errno));
	}

	/* binder device removal passed */
	ksft_inc_pass_cnt();

	ret = unlink("/dev/binderfs/binder-control");
	if (!ret) {
		keep ? : rmdir_protect_errno("/dev/binderfs");
		ksft_exit_fail_msg("Managed to delete binder-control device\n");
	} else if (errno != EPERM) {
		keep ? : rmdir_protect_errno("/dev/binderfs");
		ksft_exit_fail_msg(
			"%s - Failed to delete binder-control device but exited with unexpected error code\n",
			strerror(errno));
	}

	/* binder-control device removal failed as expected */
	ksft_inc_xfail_cnt();

on_error:
	ret = umount2("/dev/binderfs", MNT_DETACH);
	keep ?: rmdir_protect_errno("/dev/binderfs");
	if (ret < 0)
		ksft_exit_fail_msg("%s - Failed to unmount binderfs\n",
				   strerror(errno));

	/* binderfs unmount test passed */
	ksft_inc_pass_cnt();
}