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

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  E (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_fsconfig (int,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSCONFIG_CMD_CREATE ; 
 int /*<<< orphan*/  FSCONFIG_SET_STRING ; 
 int /*<<< orphan*/  MOUNT_ATTR_RDONLY ; 
 int /*<<< orphan*/  MOVE_MOUNT_F_EMPTY_PATH ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fsmount (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_error (int,char*) ; 
 scalar_t__ move_mount (int,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

int main(int argc, char *argv[])
{
	int fsfd, mfd;

	/* Mount a publically available AFS filesystem */
	fsfd = fsopen("afs", 0);
	if (fsfd == -1) {
		perror("fsopen");
		exit(1);
	}

	E_fsconfig(fsfd, FSCONFIG_SET_STRING, "source", "#grand.central.org:root.cell.", 0);
	E_fsconfig(fsfd, FSCONFIG_CMD_CREATE, NULL, NULL, 0);

	mfd = fsmount(fsfd, 0, MOUNT_ATTR_RDONLY);
	if (mfd < 0)
		mount_error(fsfd, "fsmount");
	E(close(fsfd));

	if (move_mount(mfd, "", AT_FDCWD, "/mnt", MOVE_MOUNT_F_EMPTY_PATH) < 0) {
		perror("move_mount");
		exit(1);
	}

	E(close(mfd));
	exit(0);
}