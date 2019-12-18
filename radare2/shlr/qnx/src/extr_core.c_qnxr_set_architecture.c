#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_3__ {int architecture; int /*<<< orphan*/  registers; } ;
typedef  TYPE_1__ libqnxr_t ;

/* Variables and functions */
#define  ARCH_ARM_32 129 
#define  ARCH_X86_32 128 
 int /*<<< orphan*/  arm32 ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  x86_32 ; 

int qnxr_set_architecture (libqnxr_t *g, ut8 architecture) {
	if (!g) return -1;
	g->architecture = architecture;
	switch (architecture) {
	case ARCH_X86_32:
		g->registers = x86_32;
		break;
	case ARCH_ARM_32:
		g->registers = arm32;
		break;
	default:
		eprintf ("Error unknown architecture set\n");
	}
	return 0;
}