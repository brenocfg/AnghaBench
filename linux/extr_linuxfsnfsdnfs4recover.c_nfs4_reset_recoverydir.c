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
struct path {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int ENOTDIR ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 scalar_t__ d_is_dir (int /*<<< orphan*/ ) ; 
 int kern_path (char*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  user_recovery_dirname ; 

int
nfs4_reset_recoverydir(char *recdir)
{
	int status;
	struct path path;

	status = kern_path(recdir, LOOKUP_FOLLOW, &path);
	if (status)
		return status;
	status = -ENOTDIR;
	if (d_is_dir(path.dentry)) {
		strcpy(user_recovery_dirname, recdir);
		status = 0;
	}
	path_put(&path);
	return status;
}