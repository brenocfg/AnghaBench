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
struct TYPE_2__ {int ah; int dl; int al; } ;
union REGS {TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetCurrentDirectory (char*) ; 
 int /*<<< orphan*/  intdos (union REGS*,union REGS*) ; 

int
change_drive(int drive)
{
#ifdef WIN3264
    char temp[3] = "-:";
    temp[0] = (char)(drive + 'A' - 1);
    return !SetCurrentDirectory(temp);
#else
# ifndef UNIX_LINT
    union REGS regs;

    regs.h.ah = 0x0e;
    regs.h.dl = drive - 1;
    intdos(&regs, &regs);   /* set default drive */
    regs.h.ah = 0x19;
    intdos(&regs, &regs);   /* get default drive */
    if (regs.h.al == drive - 1)
	return 0;
# endif
    return -1;
#endif
}