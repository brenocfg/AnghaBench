#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* io; } ;
struct TYPE_14__ {TYPE_3__ iob; } ;
struct TYPE_13__ {TYPE_4__* bfvm; } ;
struct TYPE_12__ {int /*<<< orphan*/  input; int /*<<< orphan*/  screen; int /*<<< orphan*/  base; } ;
struct TYPE_10__ {TYPE_1__* desc; } ;
struct TYPE_9__ {TYPE_5__* data; } ;
typedef  TYPE_5__ RIOBdescbg ;
typedef  TYPE_6__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  is_io_esil (TYPE_6__*) ; 

__attribute__((used)) static int __esil_attach(RDebug *dbg, int pid) {
	eprintf ("OK attach\n");
	return true;
#if 0
	if (!is_io_esil (dbg))
		return false;
#endif
#if 0
	RIOBdescbg *o;
	o = dbg->iob.io->desc->data;
eprintf ("base = %llx\n", o->bfvm->base);
eprintf ("screen = %llx\n", o->bfvm->screen);
eprintf ("input = %llx\n", o->bfvm->input);
#endif
	return true;
}