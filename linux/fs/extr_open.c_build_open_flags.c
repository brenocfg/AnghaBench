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
typedef  int umode_t ;
struct open_flags {int mode; int open_flag; int acc_mode; int lookup_flags; int /*<<< orphan*/  intent; } ;

/* Variables and functions */
 int ACC_MODE (int) ; 
 int EINVAL ; 
 int FMODE_NONOTIFY ; 
 int /*<<< orphan*/  LOOKUP_CREATE ; 
 int LOOKUP_DIRECTORY ; 
 int /*<<< orphan*/  LOOKUP_EXCL ; 
 int LOOKUP_FOLLOW ; 
 int /*<<< orphan*/  LOOKUP_OPEN ; 
 int MAY_APPEND ; 
 int MAY_WRITE ; 
 int O_APPEND ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_DIRECTORY ; 
 int O_DSYNC ; 
 int O_EXCL ; 
 int O_NOFOLLOW ; 
 int O_PATH ; 
 int O_TMPFILE ; 
 int O_TMPFILE_MASK ; 
 int O_TRUNC ; 
 int S_IALLUGO ; 
 int S_IFREG ; 
 int VALID_OPEN_FLAGS ; 
 int __O_SYNC ; 
 int __O_TMPFILE ; 

__attribute__((used)) static inline int build_open_flags(int flags, umode_t mode, struct open_flags *op)
{
	int lookup_flags = 0;
	int acc_mode = ACC_MODE(flags);

	/*
	 * Clear out all open flags we don't know about so that we don't report
	 * them in fcntl(F_GETFD) or similar interfaces.
	 */
	flags &= VALID_OPEN_FLAGS;

	if (flags & (O_CREAT | __O_TMPFILE))
		op->mode = (mode & S_IALLUGO) | S_IFREG;
	else
		op->mode = 0;

	/* Must never be set by userspace */
	flags &= ~FMODE_NONOTIFY & ~O_CLOEXEC;

	/*
	 * O_SYNC is implemented as __O_SYNC|O_DSYNC.  As many places only
	 * check for O_DSYNC if the need any syncing at all we enforce it's
	 * always set instead of having to deal with possibly weird behaviour
	 * for malicious applications setting only __O_SYNC.
	 */
	if (flags & __O_SYNC)
		flags |= O_DSYNC;

	if (flags & __O_TMPFILE) {
		if ((flags & O_TMPFILE_MASK) != O_TMPFILE)
			return -EINVAL;
		if (!(acc_mode & MAY_WRITE))
			return -EINVAL;
	} else if (flags & O_PATH) {
		/*
		 * If we have O_PATH in the open flag. Then we
		 * cannot have anything other than the below set of flags
		 */
		flags &= O_DIRECTORY | O_NOFOLLOW | O_PATH;
		acc_mode = 0;
	}

	op->open_flag = flags;

	/* O_TRUNC implies we need access checks for write permissions */
	if (flags & O_TRUNC)
		acc_mode |= MAY_WRITE;

	/* Allow the LSM permission hook to distinguish append
	   access from general write access. */
	if (flags & O_APPEND)
		acc_mode |= MAY_APPEND;

	op->acc_mode = acc_mode;

	op->intent = flags & O_PATH ? 0 : LOOKUP_OPEN;

	if (flags & O_CREAT) {
		op->intent |= LOOKUP_CREATE;
		if (flags & O_EXCL)
			op->intent |= LOOKUP_EXCL;
	}

	if (flags & O_DIRECTORY)
		lookup_flags |= LOOKUP_DIRECTORY;
	if (!(flags & O_NOFOLLOW))
		lookup_flags |= LOOKUP_FOLLOW;
	op->lookup_flags = lookup_flags;
	return 0;
}