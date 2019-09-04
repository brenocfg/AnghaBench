#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WindCtx ;
struct TYPE_9__ {TYPE_2__* io; } ;
struct TYPE_11__ {scalar_t__ pid; scalar_t__ arch; TYPE_3__ iob; } ;
struct TYPE_10__ {scalar_t__ data; TYPE_1__* plugin; } ;
struct TYPE_8__ {TYPE_4__* desc; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ RIODesc ;
typedef  TYPE_5__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * wctx ; 
 int /*<<< orphan*/  windbg_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  windbg_read_ver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  windbg_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r_debug_windbg_attach(RDebug *dbg, int pid) {
	RIODesc *desc = dbg->iob.io->desc;

	if (!desc || !desc->plugin || !desc->plugin->name || !desc->data) {
		return false;
	}
	if (strncmp (desc->plugin->name, "windbg", 6)) {
		return false;
	}
	if (dbg->arch && strcmp (dbg->arch, "x86")) {
		return false;
	}
	wctx = (WindCtx *)desc->data;

	// Handshake
	if (!windbg_sync (wctx)) {
		eprintf ("Could not connect to windbg\n");
		windbg_ctx_free (wctx);
		return false;
	}
	if (!windbg_read_ver (wctx)) {
		windbg_ctx_free (wctx);
		return false;
	}

	// Make r_debug_is_dead happy
	dbg->pid = 0;
	return true;
}