#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * mem; } ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ active; } ;
struct TYPE_6__ {scalar_t__ num; } ;
struct TYPE_9__ {int last_was_newline; int socket_fd; int socket_server_fd; scalar_t__ last_line; int /*<<< orphan*/ * cur_command; int /*<<< orphan*/ * stdin_file; int /*<<< orphan*/  eol; int /*<<< orphan*/  swd; int /*<<< orphan*/  sigio_watcher_thread; int /*<<< orphan*/ * oplog_list; int /*<<< orphan*/ * sigsegv_bailout; TYPE_3__ sigsafe_mem; scalar_t__ input_buflen; TYPE_2__ err_buf; scalar_t__ req_id; scalar_t__ unclean_eval; int /*<<< orphan*/ * sapi_name_ptr; TYPE_1__ frame; int /*<<< orphan*/ * io; int /*<<< orphan*/ * oplog; int /*<<< orphan*/  flags; scalar_t__ bp_count; scalar_t__ in_execution; scalar_t__ vmret; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * buffer; scalar_t__ exec_len; int /*<<< orphan*/ * exec; int /*<<< orphan*/  lines; int /*<<< orphan*/ ** colors; int /*<<< orphan*/ ** prompt; } ;
typedef  TYPE_4__ zend_phpdbg_globals ;
struct win32_sigio_watcher_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  PHPDBG_DEFAULT_FLAGS ; 
 int /*<<< orphan*/  PHPDBG_EOL_LF ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phpdbg_get_terminal_height () ; 

__attribute__((used)) static inline void php_phpdbg_globals_ctor(zend_phpdbg_globals *pg) /* {{{ */
{
	pg->prompt[0] = NULL;
	pg->prompt[1] = NULL;

	pg->colors[0] = NULL;
	pg->colors[1] = NULL;
	pg->colors[2] = NULL;

	pg->lines = phpdbg_get_terminal_height();
	pg->exec = NULL;
	pg->exec_len = 0;
	pg->buffer = NULL;
	pg->last_was_newline = 1;
	pg->ops = NULL;
	pg->vmret = 0;
	pg->in_execution = 0;
	pg->bp_count = 0;
	pg->flags = PHPDBG_DEFAULT_FLAGS;
	pg->oplog = NULL;
	memset(pg->io, 0, sizeof(pg->io));
	pg->frame.num = 0;
	pg->sapi_name_ptr = NULL;
	pg->socket_fd = -1;
	pg->socket_server_fd = -1;
	pg->unclean_eval = 0;

	pg->req_id = 0;
	pg->err_buf.active = 0;
	pg->err_buf.type = 0;

	pg->input_buflen = 0;
	pg->sigsafe_mem.mem = NULL;
	pg->sigsegv_bailout = NULL;

	pg->oplog_list = NULL;

#ifdef PHP_WIN32
	pg->sigio_watcher_thread = INVALID_HANDLE_VALUE;
	memset(&pg->swd, 0, sizeof(struct win32_sigio_watcher_data));
#endif

	pg->eol = PHPDBG_EOL_LF;

	pg->stdin_file = NULL;

	pg->cur_command = NULL;
	pg->last_line = 0;
}