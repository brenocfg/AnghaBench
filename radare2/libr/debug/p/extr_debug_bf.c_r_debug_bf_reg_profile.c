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
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 char* strdup (char*) ; 

__attribute__((used)) static char *r_debug_bf_reg_profile(RDebug *dbg) {
	return strdup (
	"=PC	pc\n"
	"=SP	esp\n"
	"=BP	ptr\n"
	"gpr	pc	.32	0	0\n"
	"gpr	ptr	.32	4	0\n"
	"gpr	esp	.32	8	0\n"
	"gpr	scr	.32	12	0\n"
	"gpr	scri	.32	16	0\n"
	"gpr	inp	.32	20	0\n"
	"gpr	inpi	.32	24	0\n"
	"gpr	mem	.32	28	0\n"
	"gpr	memi	.32	32	0\n"
	);
}