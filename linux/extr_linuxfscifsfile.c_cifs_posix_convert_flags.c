#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 unsigned int O_ACCMODE ; 
 unsigned int O_CREAT ; 
 unsigned int O_DIRECT ; 
 unsigned int O_DIRECTORY ; 
 unsigned int O_DSYNC ; 
 unsigned int O_EXCL ; 
 unsigned int O_NOFOLLOW ; 
 unsigned int O_RDONLY ; 
 unsigned int O_RDWR ; 
 unsigned int O_TRUNC ; 
 unsigned int O_WRONLY ; 
 int /*<<< orphan*/  SMB_O_CREAT ; 
 int /*<<< orphan*/  SMB_O_DIRECT ; 
 int /*<<< orphan*/  SMB_O_DIRECTORY ; 
 int /*<<< orphan*/  SMB_O_EXCL ; 
 int /*<<< orphan*/  SMB_O_NOFOLLOW ; 
 int /*<<< orphan*/  SMB_O_RDONLY ; 
 int /*<<< orphan*/  SMB_O_RDWR ; 
 int /*<<< orphan*/  SMB_O_SYNC ; 
 int /*<<< orphan*/  SMB_O_TRUNC ; 
 int /*<<< orphan*/  SMB_O_WRONLY ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 

__attribute__((used)) static u32 cifs_posix_convert_flags(unsigned int flags)
{
	u32 posix_flags = 0;

	if ((flags & O_ACCMODE) == O_RDONLY)
		posix_flags = SMB_O_RDONLY;
	else if ((flags & O_ACCMODE) == O_WRONLY)
		posix_flags = SMB_O_WRONLY;
	else if ((flags & O_ACCMODE) == O_RDWR)
		posix_flags = SMB_O_RDWR;

	if (flags & O_CREAT) {
		posix_flags |= SMB_O_CREAT;
		if (flags & O_EXCL)
			posix_flags |= SMB_O_EXCL;
	} else if (flags & O_EXCL)
		cifs_dbg(FYI, "Application %s pid %d has incorrectly set O_EXCL flag but not O_CREAT on file open. Ignoring O_EXCL\n",
			 current->comm, current->tgid);

	if (flags & O_TRUNC)
		posix_flags |= SMB_O_TRUNC;
	/* be safe and imply O_SYNC for O_DSYNC */
	if (flags & O_DSYNC)
		posix_flags |= SMB_O_SYNC;
	if (flags & O_DIRECTORY)
		posix_flags |= SMB_O_DIRECTORY;
	if (flags & O_NOFOLLOW)
		posix_flags |= SMB_O_NOFOLLOW;
	if (flags & O_DIRECT)
		posix_flags |= SMB_O_DIRECT;

	return posix_flags;
}