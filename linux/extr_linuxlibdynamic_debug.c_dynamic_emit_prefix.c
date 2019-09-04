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
struct _ddebug {int flags; char* modname; char* function; int lineno; } ;

/* Variables and functions */
 int PREFIX_SIZE ; 
 int _DPRINTK_FLAGS_INCL_FUNCNAME ; 
 int _DPRINTK_FLAGS_INCL_LINENO ; 
 int _DPRINTK_FLAGS_INCL_MODNAME ; 
 int _DPRINTK_FLAGS_INCL_TID ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  remaining (int) ; 
 scalar_t__ snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int task_pid_vnr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *dynamic_emit_prefix(const struct _ddebug *desc, char *buf)
{
	int pos_after_tid;
	int pos = 0;

	*buf = '\0';

	if (desc->flags & _DPRINTK_FLAGS_INCL_TID) {
		if (in_interrupt())
			pos += snprintf(buf + pos, remaining(pos), "<intr> ");
		else
			pos += snprintf(buf + pos, remaining(pos), "[%d] ",
					task_pid_vnr(current));
	}
	pos_after_tid = pos;
	if (desc->flags & _DPRINTK_FLAGS_INCL_MODNAME)
		pos += snprintf(buf + pos, remaining(pos), "%s:",
				desc->modname);
	if (desc->flags & _DPRINTK_FLAGS_INCL_FUNCNAME)
		pos += snprintf(buf + pos, remaining(pos), "%s:",
				desc->function);
	if (desc->flags & _DPRINTK_FLAGS_INCL_LINENO)
		pos += snprintf(buf + pos, remaining(pos), "%d:",
				desc->lineno);
	if (pos - pos_after_tid)
		pos += snprintf(buf + pos, remaining(pos), " ");
	if (pos >= PREFIX_SIZE)
		buf[PREFIX_SIZE - 1] = '\0';

	return buf;
}