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
typedef  int /*<<< orphan*/  u16 ;
struct file {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_OPT_NONE ; 
 int /*<<< orphan*/  CAP_SYS_TTY_CONFIG ; 
#define  FIBMAP 138 
#define  FIGETBSZ 137 
 int /*<<< orphan*/  FILE__GETATTR ; 
 int /*<<< orphan*/  FILE__IOCTL ; 
 int /*<<< orphan*/  FILE__SETATTR ; 
#define  FIOASYNC 136 
#define  FIONBIO 135 
#define  FIONREAD 134 
#define  FS_IOC_GETFLAGS 133 
#define  FS_IOC_GETVERSION 132 
#define  FS_IOC_SETFLAGS 131 
#define  FS_IOC_SETVERSION 130 
#define  KDSKBENT 129 
#define  KDSKBSENT 128 
 int cred_has_capability (struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cred* current_cred () ; 
 int file_has_perm (struct cred const*,struct file*,int /*<<< orphan*/ ) ; 
 int ioctl_has_perm (struct cred const*,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_file_ioctl(struct file *file, unsigned int cmd,
			      unsigned long arg)
{
	const struct cred *cred = current_cred();
	int error = 0;

	switch (cmd) {
	case FIONREAD:
	/* fall through */
	case FIBMAP:
	/* fall through */
	case FIGETBSZ:
	/* fall through */
	case FS_IOC_GETFLAGS:
	/* fall through */
	case FS_IOC_GETVERSION:
		error = file_has_perm(cred, file, FILE__GETATTR);
		break;

	case FS_IOC_SETFLAGS:
	/* fall through */
	case FS_IOC_SETVERSION:
		error = file_has_perm(cred, file, FILE__SETATTR);
		break;

	/* sys_ioctl() checks */
	case FIONBIO:
	/* fall through */
	case FIOASYNC:
		error = file_has_perm(cred, file, 0);
		break;

	case KDSKBENT:
	case KDSKBSENT:
		error = cred_has_capability(cred, CAP_SYS_TTY_CONFIG,
					    CAP_OPT_NONE, true);
		break;

	/* default case assumes that the command will go
	 * to the file's ioctl() function.
	 */
	default:
		error = ioctl_has_perm(cred, file, FILE__IOCTL, (u16) cmd);
	}
	return error;
}