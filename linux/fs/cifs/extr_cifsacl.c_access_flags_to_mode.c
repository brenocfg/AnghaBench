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
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ACCESS_ALLOWED ; 
 int ACCESS_DENIED ; 
 int FILE_EXEC_RIGHTS ; 
 int FILE_READ_RIGHTS ; 
 int FILE_WRITE_RIGHTS ; 
 int GENERIC_ALL ; 
 int GENERIC_EXECUTE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  NOISY ; 
 int S_IRUGO ; 
 int S_IRWXUGO ; 
 int S_IWUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void access_flags_to_mode(__le32 ace_flags, int type, umode_t *pmode,
				 umode_t *pbits_to_set)
{
	__u32 flags = le32_to_cpu(ace_flags);
	/* the order of ACEs is important.  The canonical order is to begin with
	   DENY entries followed by ALLOW, otherwise an allow entry could be
	   encountered first, making the subsequent deny entry like "dead code"
	   which would be superflous since Windows stops when a match is made
	   for the operation you are trying to perform for your user */

	/* For deny ACEs we change the mask so that subsequent allow access
	   control entries do not turn on the bits we are denying */
	if (type == ACCESS_DENIED) {
		if (flags & GENERIC_ALL)
			*pbits_to_set &= ~S_IRWXUGO;

		if ((flags & GENERIC_WRITE) ||
			((flags & FILE_WRITE_RIGHTS) == FILE_WRITE_RIGHTS))
			*pbits_to_set &= ~S_IWUGO;
		if ((flags & GENERIC_READ) ||
			((flags & FILE_READ_RIGHTS) == FILE_READ_RIGHTS))
			*pbits_to_set &= ~S_IRUGO;
		if ((flags & GENERIC_EXECUTE) ||
			((flags & FILE_EXEC_RIGHTS) == FILE_EXEC_RIGHTS))
			*pbits_to_set &= ~S_IXUGO;
		return;
	} else if (type != ACCESS_ALLOWED) {
		cifs_dbg(VFS, "unknown access control type %d\n", type);
		return;
	}
	/* else ACCESS_ALLOWED type */

	if (flags & GENERIC_ALL) {
		*pmode |= (S_IRWXUGO & (*pbits_to_set));
		cifs_dbg(NOISY, "all perms\n");
		return;
	}
	if ((flags & GENERIC_WRITE) ||
			((flags & FILE_WRITE_RIGHTS) == FILE_WRITE_RIGHTS))
		*pmode |= (S_IWUGO & (*pbits_to_set));
	if ((flags & GENERIC_READ) ||
			((flags & FILE_READ_RIGHTS) == FILE_READ_RIGHTS))
		*pmode |= (S_IRUGO & (*pbits_to_set));
	if ((flags & GENERIC_EXECUTE) ||
			((flags & FILE_EXEC_RIGHTS) == FILE_EXEC_RIGHTS))
		*pmode |= (S_IXUGO & (*pbits_to_set));

	cifs_dbg(NOISY, "access flags 0x%x mode now 0x%x\n", flags, *pmode);
	return;
}