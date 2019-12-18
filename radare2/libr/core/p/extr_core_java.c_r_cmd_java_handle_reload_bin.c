#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
struct TYPE_9__ {int /*<<< orphan*/  io; TYPE_1__* file; } ;
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ RCore ;
typedef  int /*<<< orphan*/  RBinJavaObj ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 scalar_t__ JAVA_CMDS ; 
 scalar_t__ RELOAD_BIN_IDX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_anal (TYPE_2__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* r_cmd_java_consumetok (char const*,char,int) ; 
 scalar_t__ r_cmd_java_get_bin_obj (int /*<<< orphan*/ *) ; 
 int r_cmd_java_get_input_num_value (TYPE_2__*,char const*) ; 
 scalar_t__ r_cmd_java_is_valid_input_num_value (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  r_cmd_java_print_cmd_help (scalar_t__) ; 
 int r_cmd_java_reload_bin_from_buf (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_io_read_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int r_io_size (int /*<<< orphan*/ ) ; 
 int r_io_use_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_cmd_java_handle_reload_bin (RCore *core, const char *cmd) {
	RAnal *anal = get_anal (core);
	RBinJavaObj *obj = (RBinJavaObj *) r_cmd_java_get_bin_obj (anal);
	const char *p = cmd;
	ut64 addr = 0LL; //cur_offset = core->offset, addr = 0;
	ut64 buf_size = 0;
	ut8 * buf = NULL;
	int res = false;

	if (*cmd == ' ') {
		p = r_cmd_java_consumetok (p, ' ', -1);
	}
	if (!*cmd) {
		r_cmd_java_print_cmd_help (JAVA_CMDS+RELOAD_BIN_IDX);
		return true;
	}

	addr = r_cmd_java_is_valid_input_num_value(core, p) ? r_cmd_java_get_input_num_value (core, p) : -1;
	if (*cmd == ' ') {
		p = r_cmd_java_consumetok (p, ' ', -1);
	}
	buf_size = r_cmd_java_is_valid_input_num_value(core, p) ? r_cmd_java_get_input_num_value (core, p) : -1;

	// XXX this may cause problems cause the file we are looking at may not be the bin we want.
	// lets pretend it is for now
	if (buf_size == 0) {
		res = r_io_use_fd (core->io, core->file->fd);
		buf_size = r_io_size (core->io);
		buf = malloc (buf_size);
		memset (buf, 0, buf_size);
		r_io_read_at (core->io, addr, buf, buf_size);
	}
	if (buf && obj) {
		res = r_cmd_java_reload_bin_from_buf (core, obj, buf, buf_size);
	}
	free (buf);
	return res;
}