#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* io; } ;
struct TYPE_13__ {int swstep; TYPE_3__ iob; } ;
struct TYPE_12__ {int /*<<< orphan*/  desc; } ;
struct TYPE_11__ {TYPE_5__* data; TYPE_1__* plugin; } ;
struct TYPE_9__ {TYPE_4__* desc; } ;
struct TYPE_8__ {scalar_t__ name; } ;
typedef  TYPE_4__ RIODesc ;
typedef  TYPE_5__ RIOBochs ;
typedef  TYPE_6__ RDebug ;

/* Variables and functions */
 int bBreak ; 
 int bCapturaRegs ; 
 int bStep ; 
 int /*<<< orphan*/ * desc ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  saveRegs ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 

__attribute__((used)) static int r_debug_bochs_attach(RDebug *dbg, int pid) {
	RIODesc *d = dbg->iob.io->desc;
	//eprintf ("bochs_attach:\n");
	dbg->swstep = false;
	if (d && d->plugin && d->plugin->name && d->data) {
		if (!strcmp ("bochs", d->plugin->name)) {
			RIOBochs *g = d->data;
			//int arch = r_sys_arch_id (dbg->arch);
			// int bits = dbg->anal->bits;
			if (( desc = &g->desc )) {
				eprintf("bochs attach: ok\n");
				saveRegs = malloc(1024);
				bCapturaRegs = true;
				bStep = false;
				bBreak = false;
			}
		}
	}
	return true;
}