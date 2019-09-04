#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char ut8 ;
struct TYPE_8__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  io; TYPE_1__* file; int /*<<< orphan*/  num; int /*<<< orphan*/  config; } ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  WSEEK (TYPE_2__*,int) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_core_block_read (TYPE_2__*) ; 
 char* r_core_editor (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ r_file_slurp (char*,int*) ; 
 int /*<<< orphan*/  r_io_use_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_io_write_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int r_num_math (int /*<<< orphan*/ ,char*) ; 
 char* r_str_trim (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool cmd_wff(RCore *core, const char *input) {
	ut8 *buf;
	int size;
	// XXX: file names cannot contain spaces
	const char *arg = input + ((input[1] == ' ') ? 2 : 1);
	int wseek = r_config_get_i (core->config, "cfg.wseek");
	char *p, *a = r_str_trim (strdup (arg));
	p = strchr (a, ' ');
	if (p) {
		*p++ = 0;
	}

	if (*arg =='?' || !*arg) {
		eprintf ("Usage: wf [file] ([size] ([offset]))\n");
	}
	if (!strcmp (arg, "-")) {
		char *out = r_core_editor (core, NULL, NULL);
		if (out) {
			r_io_write_at (core->io, core->offset,
				(ut8*)out, strlen (out));
			r_core_block_read (core);
			free (out);
		}
	}
	if ((buf = (ut8*) r_file_slurp (a, &size))) {
		int u_offset = 0;
		int u_size = r_num_math (core->num, p);
		if (u_size < 1) u_size = size;
		if (p) {
			*p++ = 0;
			u_offset = r_num_math (core->num, p);
			if (u_offset > size) {
				eprintf ("Invalid offset\n");
				free (buf);
				return false;
			}
		}
		r_io_use_fd (core->io, core->file->fd);
		r_io_write_at (core->io, core->offset, buf + u_offset, u_size);
		WSEEK (core, size);
		free (buf);
		r_core_block_read (core);
	} else {
		eprintf ("Cannot open file '%s'\n", arg);
	}
	return true;
}