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
struct file {int dummy; } ;

/* Variables and functions */
#define  COMEDI32_CHANINFO 144 
#define  COMEDI32_CMD 143 
#define  COMEDI32_CMDTEST 142 
#define  COMEDI32_INSN 141 
#define  COMEDI32_INSNLIST 140 
#define  COMEDI32_RANGEINFO 139 
#define  COMEDI_BUFCONFIG 138 
#define  COMEDI_BUFINFO 137 
#define  COMEDI_CANCEL 136 
#define  COMEDI_DEVCONFIG 135 
#define  COMEDI_DEVINFO 134 
#define  COMEDI_LOCK 133 
#define  COMEDI_POLL 132 
#define  COMEDI_SETRSUBD 131 
#define  COMEDI_SETWSUBD 130 
#define  COMEDI_SUBDINFO 129 
#define  COMEDI_UNLOCK 128 
 int ENOIOCTLCMD ; 
 int compat_chaninfo (struct file*,unsigned long) ; 
 int compat_cmd (struct file*,unsigned long) ; 
 int compat_cmdtest (struct file*,unsigned long) ; 
 int compat_insn (struct file*,unsigned long) ; 
 int compat_insnlist (struct file*,unsigned long) ; 
 scalar_t__ compat_ptr (unsigned long) ; 
 int compat_rangeinfo (struct file*,unsigned long) ; 
 int translated_ioctl (struct file*,unsigned int,unsigned long) ; 

long comedi_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int rc;

	switch (cmd) {
	case COMEDI_DEVCONFIG:
	case COMEDI_DEVINFO:
	case COMEDI_SUBDINFO:
	case COMEDI_BUFCONFIG:
	case COMEDI_BUFINFO:
		/* Just need to translate the pointer argument. */
		arg = (unsigned long)compat_ptr(arg);
		rc = translated_ioctl(file, cmd, arg);
		break;
	case COMEDI_LOCK:
	case COMEDI_UNLOCK:
	case COMEDI_CANCEL:
	case COMEDI_POLL:
	case COMEDI_SETRSUBD:
	case COMEDI_SETWSUBD:
		/* No translation needed. */
		rc = translated_ioctl(file, cmd, arg);
		break;
	case COMEDI32_CHANINFO:
		rc = compat_chaninfo(file, arg);
		break;
	case COMEDI32_RANGEINFO:
		rc = compat_rangeinfo(file, arg);
		break;
	case COMEDI32_CMD:
		rc = compat_cmd(file, arg);
		break;
	case COMEDI32_CMDTEST:
		rc = compat_cmdtest(file, arg);
		break;
	case COMEDI32_INSNLIST:
		rc = compat_insnlist(file, arg);
		break;
	case COMEDI32_INSN:
		rc = compat_insn(file, arg);
		break;
	default:
		rc = -ENOIOCTLCMD;
		break;
	}
	return rc;
}