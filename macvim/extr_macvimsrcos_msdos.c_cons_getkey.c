#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ah; int dl; int al; } ;
struct TYPE_3__ {int flags; } ;
union REGS {TYPE_2__ h; TYPE_1__ x; } ;

/* Variables and functions */
 int cons_key ; 
 int /*<<< orphan*/  intdos (union REGS*,union REGS*) ; 

__attribute__((used)) static void
cons_getkey(void)
{
    union REGS regs;

    /* call DOS function 6: Direct console I/O */
    regs.h.ah = 0x06;
    regs.h.dl = 0xff;
    (void)intdos(&regs, &regs);
    if ((regs.x.flags & 0x40) == 0)	/* zero flag not set? */
	cons_key = (regs.h.al & 0xff);
}