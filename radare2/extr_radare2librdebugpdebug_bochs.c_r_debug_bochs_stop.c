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

__attribute__((used)) static int r_debug_bochs_stop(RDebug *dbg) {
	//eprintf("bochs_stop:\n");
	//RIOBdescbg *o = dbg->iob.io->desc->data;
	//BfvmCPU *c = o->bfvm;
	//c->breaked = true;
	return true;
}