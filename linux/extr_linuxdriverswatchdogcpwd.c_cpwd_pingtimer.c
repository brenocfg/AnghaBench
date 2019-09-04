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
struct cpwd {TYPE_1__* devs; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ WD_DCNTR ; 
 scalar_t__ WD_STATUS ; 
 int WD_S_RUNNING ; 
 int cpwd_readb (scalar_t__) ; 
 int /*<<< orphan*/  cpwd_readw (scalar_t__) ; 

__attribute__((used)) static void cpwd_pingtimer(struct cpwd *p, int index)
{
	if (cpwd_readb(p->devs[index].regs + WD_STATUS) & WD_S_RUNNING)
		cpwd_readw(p->devs[index].regs + WD_DCNTR);
}