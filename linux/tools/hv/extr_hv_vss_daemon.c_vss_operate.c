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
struct stat {int /*<<< orphan*/  st_rdev; } ;
struct mntent {char* mnt_type; char* mnt_dir; int /*<<< orphan*/  mnt_fsname; } ;
typedef  int /*<<< orphan*/  errdir ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int FIFREEZE ; 
 unsigned int FITHAW ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MNTOPT_RO ; 
#define  VSS_OP_FREEZE 129 
#define  VSS_OP_THAW 128 
 int /*<<< orphan*/  endmntent (int /*<<< orphan*/ *) ; 
 int errno ; 
 struct mntent* getmntent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hasmntopt (struct mntent*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dev_loop (char*) ; 
 int major (int /*<<< orphan*/ ) ; 
 int minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * setmntent (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int vss_do_freeze (char*,unsigned int) ; 

__attribute__((used)) static int vss_operate(int operation)
{
	char match[] = "/dev/";
	FILE *mounts;
	struct mntent *ent;
	struct stat sb;
	char errdir[1024] = {0};
	char blkdir[23]; /* /sys/dev/block/XXX:XXX */
	unsigned int cmd;
	int error = 0, root_seen = 0, save_errno = 0;

	switch (operation) {
	case VSS_OP_FREEZE:
		cmd = FIFREEZE;
		break;
	case VSS_OP_THAW:
		cmd = FITHAW;
		break;
	default:
		return -1;
	}

	mounts = setmntent("/proc/mounts", "r");
	if (mounts == NULL)
		return -1;

	while ((ent = getmntent(mounts))) {
		if (strncmp(ent->mnt_fsname, match, strlen(match)))
			continue;
		if (stat(ent->mnt_fsname, &sb)) {
			syslog(LOG_ERR, "Can't stat: %s; error:%d %s!",
			       ent->mnt_fsname, errno, strerror(errno));
		} else {
			sprintf(blkdir, "/sys/dev/block/%d:%d",
				major(sb.st_rdev), minor(sb.st_rdev));
			if (is_dev_loop(blkdir))
				continue;
		}
		if (hasmntopt(ent, MNTOPT_RO) != NULL)
			continue;
		if (strcmp(ent->mnt_type, "vfat") == 0)
			continue;
		if (strcmp(ent->mnt_dir, "/") == 0) {
			root_seen = 1;
			continue;
		}
		error |= vss_do_freeze(ent->mnt_dir, cmd);
		if (error && operation == VSS_OP_FREEZE)
			goto err;
	}

	endmntent(mounts);

	if (root_seen) {
		error |= vss_do_freeze("/", cmd);
		if (error && operation == VSS_OP_FREEZE)
			goto err;
	}

	goto out;
err:
	save_errno = errno;
	if (ent) {
		strncpy(errdir, ent->mnt_dir, sizeof(errdir)-1);
		endmntent(mounts);
	}
	vss_operate(VSS_OP_THAW);
	/* Call syslog after we thaw all filesystems */
	if (ent)
		syslog(LOG_ERR, "FREEZE of %s failed; error:%d %s",
		       errdir, save_errno, strerror(save_errno));
	else
		syslog(LOG_ERR, "FREEZE of / failed; error:%d %s", save_errno,
		       strerror(save_errno));
out:
	return error;
}