#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_17__ {int /*<<< orphan*/  value; } ;
struct TYPE_16__ {TYPE_2__* num; int /*<<< orphan*/  yank_buf; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_y ; 
 int /*<<< orphan*/ * r_buf_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_buf_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_yank (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_yank_cat (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_yank_cat_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_yank_dump (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_yank_file_all (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_core_yank_file_ex (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_core_yank_hexdump (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_yank_hexpair (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_core_yank_paste (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_yank_set (TYPE_1__*,long long,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_core_yank_string (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_yank_to (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_file_dump (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int r_hex_str2bin (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_num_math (TYPE_2__*,char const*) ; 
 char* r_str_trim_ro (char const*) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int cmd_yank(void *data, const char *input) {
	ut64 n;
	RCore *core = (RCore *)data;
	switch (input[0]) {
	case ' ': // "y "
		r_core_yank (core, core->offset, r_num_math (core->num, input + 1));
		break;
	case 'l': // "yl"
		core->num->value = r_buf_size (core->yank_buf);
		break;
	case 'y': // "yy"
		while (input[1] == ' ') {
			input++;
		}
		n = input[1]? r_num_math (core->num, input + 1): core->offset;
		r_core_yank_paste (core, n, 0);
		break;
	case 'x': // "yx"
		r_core_yank_hexdump (core, r_num_math (core->num, input + 1));
		break;
	case 'z': // "yz"
		r_core_yank_string (core, core->offset, r_num_math (core->num, input + 1));
		break;
	case 'w': // "yw" ... we have yf which makes more sense than 'w'
		switch (input[1]) {
		case ' ':
			r_core_yank_set (core, 0, (const ut8*)input + 2, strlen (input + 2));
			break;
		case 'x':
			if (input[2] == ' ') {
				char *out = strdup (input + 3);
				int len = r_hex_str2bin (input + 3, (ut8*)out);
				if (len> 0) {
					r_core_yank_set (core, 0LL, (const ut8*)out, len);
				} else {
					eprintf ("Invalid length\n");
				}
				free (out);
			} else {
				eprintf ("Usage: ywx [hexpairs]\n");
			}
			// r_core_yank_write_hex (core, input + 2);
			break;
		default:
			eprintf ("Usage: ywx [hexpairs]\n");
			break;
		}
		break;
	case 'p': // "yp"
		r_core_yank_cat (core, r_num_math (core->num, input + 1));
		break;
	case 's': // "ys"
		r_core_yank_cat_string (core, r_num_math (core->num, input + 1));
		break;
	case 't': // "wt"
		if (input[1] == 'f') { // "wtf"
			ut64 tmpsz;
			const char *file = r_str_trim_ro (input + 2);
			const ut8 *tmp = r_buf_buffer (core->yank_buf, &tmpsz);
			if (!r_file_dump (file, tmp, tmpsz, false)) {
				eprintf ("Cannot dump to '%s'\n", file);
			}
		} else if (input[1] == ' ') {
			r_core_yank_to (core, input + 1);
		} else {
			eprintf ("Usage: wt[f] [arg] ..\n");
		}
		break;
	case 'f': // "yf"
		switch (input[1]) {
		case ' ': // "yf"
			r_core_yank_file_ex (core, input + 1);
			break;
		case 'x': // "yfx"
			r_core_yank_hexpair (core, input + 2);
			break;
		case 'a': // "yfa"
			r_core_yank_file_all (core, input + 2);
			break;
		default:
			eprintf ("Usage: yf[xa] [arg]\n");
			eprintf ("yf [file]     - copy blocksize from file into the clipboard\n");
			eprintf ("yfa [path]    - yank the whole file\n");
			eprintf ("yfx [hexpair] - yank from hexpair string\n");
			break;
		}
		break;
	case '\0': // "y"
		r_core_yank_dump (core, r_num_math (core->num, ""));
		break;
	default:
		r_core_cmd_help (core, help_msg_y);
		break;
	}
	return true;
}