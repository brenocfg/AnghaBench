#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* io; } ;
struct TYPE_12__ {TYPE_3__ iob; } ;
struct TYPE_11__ {int /*<<< orphan*/  bfvm; } ;
struct TYPE_9__ {TYPE_1__* desc; } ;
struct TYPE_8__ {TYPE_4__* data; } ;
typedef  TYPE_4__ RIOBdescbg ;
typedef  TYPE_5__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  bfvm_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_io_bf (TYPE_5__*) ; 

__attribute__((used)) static bool r_debug_bf_kill(RDebug *dbg, int pid, int tid, int sig) {
	if (!is_io_bf (dbg)) {
		return false;
	}
	RIOBdescbg *o = dbg->iob.io->desc->data;
	if (o) {
		bfvm_reset (o->bfvm);
	}
	return true;
}