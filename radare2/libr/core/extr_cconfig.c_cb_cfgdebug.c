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
struct TYPE_11__ {int va; scalar_t__ debug; } ;
struct TYPE_10__ {scalar_t__ i_value; } ;
struct TYPE_9__ {TYPE_2__* bin; scalar_t__ dbg; TYPE_1__* file; TYPE_5__* io; int /*<<< orphan*/  config; } ;
struct TYPE_8__ {int is_debugger; } ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ RCore ;
typedef  TYPE_4__ RConfigNode ;

/* Variables and functions */
 char const* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_debug_select (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_debug_use (scalar_t__,char const*) ; 
 int /*<<< orphan*/  r_io_fd_get_pid (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_io_fd_get_tid (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bool cb_cfgdebug(void *user, void *data) {
	RCore *core = (RCore*) user;
	RConfigNode *node = (RConfigNode*) data;
	if (!core) {
		return false;
	}
	if (core->io) {
		core->io->va = !node->i_value;
		core->io->debug = node->i_value;
	}
	if (core->dbg && node->i_value) {
		const char *dbgbackend = r_config_get (core->config, "dbg.backend");
		core->bin->is_debugger = true;
		r_debug_use (core->dbg, dbgbackend);
		if (!strcmp (r_config_get (core->config, "cmd.prompt"), "")) {
			r_config_set (core->config, "cmd.prompt", ".dr*");
		}
		if (!strcmp (dbgbackend, "bf")) {
			r_config_set (core->config, "asm.arch", "bf");
		}
		if (core->file) {
			r_debug_select (core->dbg, r_io_fd_get_pid (core->io, core->file->fd),
					r_io_fd_get_tid (core->io, core->file->fd));
		}
	} else {
		r_debug_use (core->dbg, NULL);
		core->bin->is_debugger = false;
	}
	return true;
}