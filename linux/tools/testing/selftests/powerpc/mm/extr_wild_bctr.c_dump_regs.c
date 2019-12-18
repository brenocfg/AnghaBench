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
struct TYPE_2__ {int* gpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int) ; 
 TYPE_1__ signal_regs ; 

__attribute__((used)) static void dump_regs(void)
{
	for (int i = 0; i < 32; i += 4) {
		printf("r%02d 0x%016lx  r%02d 0x%016lx  " \
		       "r%02d 0x%016lx  r%02d 0x%016lx\n",
		       i, signal_regs.gpr[i],
		       i+1, signal_regs.gpr[i+1],
		       i+2, signal_regs.gpr[i+2],
		       i+3, signal_regs.gpr[i+3]);
	}
}