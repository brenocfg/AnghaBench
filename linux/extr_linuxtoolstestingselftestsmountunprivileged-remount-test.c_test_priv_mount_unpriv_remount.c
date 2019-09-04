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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_NEWNS ; 
 scalar_t__ EXIT_SUCCESS ; 
 int MS_BIND ; 
 int MS_REC ; 
 int MS_REMOUNT ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  create_and_enter_userns () ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (scalar_t__) ; 
 int fork () ; 
 int mount (char const*,char const*,char*,int,int /*<<< orphan*/ *) ; 
 int read_mnt_flags (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int unshare (int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool test_priv_mount_unpriv_remount(void)
{
	pid_t child;
	int ret;
	const char *orig_path = "/dev";
	const char *dest_path = "/tmp";
	int orig_mnt_flags, remount_mnt_flags;

	child = fork();
	if (child == -1) {
		die("fork failed: %s\n",
			strerror(errno));
	}
	if (child != 0) { /* parent */
		pid_t pid;
		int status;
		pid = waitpid(child, &status, 0);
		if (pid == -1) {
			die("waitpid failed: %s\n",
				strerror(errno));
		}
		if (pid != child) {
			die("waited for %d got %d\n",
				child, pid);
		}
		if (!WIFEXITED(status)) {
			die("child did not terminate cleanly\n");
		}
		return WEXITSTATUS(status) == EXIT_SUCCESS ? true : false;
	}

	orig_mnt_flags = read_mnt_flags(orig_path);

	create_and_enter_userns();
	ret = unshare(CLONE_NEWNS);
	if (ret != 0) {
		die("unshare(CLONE_NEWNS) failed: %s\n",
			strerror(errno));
	}

	ret = mount(orig_path, dest_path, "bind", MS_BIND | MS_REC, NULL);
	if (ret != 0) {
		die("recursive bind mount of %s onto %s failed: %s\n",
			orig_path, dest_path, strerror(errno));
	}

	ret = mount(dest_path, dest_path, "none",
		    MS_REMOUNT | MS_BIND | orig_mnt_flags , NULL);
	if (ret != 0) {
		/* system("cat /proc/self/mounts"); */
		die("remount of /tmp failed: %s\n",
		    strerror(errno));
	}

	remount_mnt_flags = read_mnt_flags(dest_path);
	if (orig_mnt_flags != remount_mnt_flags) {
		die("Mount flags unexpectedly changed during remount of %s originally mounted on %s\n",
			dest_path, orig_path);
	}
	exit(EXIT_SUCCESS);
}