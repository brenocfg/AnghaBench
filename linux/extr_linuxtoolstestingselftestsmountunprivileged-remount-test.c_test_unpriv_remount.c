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
 int MS_REMOUNT ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  create_and_enter_userns () ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (scalar_t__) ; 
 int fork () ; 
 scalar_t__ mount (char*,char*,char const*,int,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ unshare (int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool test_unpriv_remount(const char *fstype, const char *mount_options,
			 int mount_flags, int remount_flags, int invalid_flags)
{
	pid_t child;

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

	create_and_enter_userns();
	if (unshare(CLONE_NEWNS) != 0) {
		die("unshare(CLONE_NEWNS) failed: %s\n",
			strerror(errno));
	}

	if (mount("testing", "/tmp", fstype, mount_flags, mount_options) != 0) {
		die("mount of %s with options '%s' on /tmp failed: %s\n",
		    fstype,
		    mount_options? mount_options : "",
		    strerror(errno));
	}

	create_and_enter_userns();

	if (unshare(CLONE_NEWNS) != 0) {
		die("unshare(CLONE_NEWNS) failed: %s\n",
			strerror(errno));
	}

	if (mount("/tmp", "/tmp", "none",
		  MS_REMOUNT | MS_BIND | remount_flags, NULL) != 0) {
		/* system("cat /proc/self/mounts"); */
		die("remount of /tmp failed: %s\n",
		    strerror(errno));
	}

	if (mount("/tmp", "/tmp", "none",
		  MS_REMOUNT | MS_BIND | invalid_flags, NULL) == 0) {
		/* system("cat /proc/self/mounts"); */
		die("remount of /tmp with invalid flags "
		    "succeeded unexpectedly\n");
	}
	exit(EXIT_SUCCESS);
}