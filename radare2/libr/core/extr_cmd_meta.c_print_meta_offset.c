#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  file ;
struct TYPE_3__ {int /*<<< orphan*/  bin; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int r_bin_addr2line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,...) ; 
 scalar_t__ r_file_exists (char*) ; 
 char* r_file_slurp_line (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool print_meta_offset(RCore *core, ut64 addr) {
	int line, line_old, i;
	char file[1024];

	int ret = r_bin_addr2line (core->bin, addr, file, sizeof (file) - 1, &line);
	if (ret) {
		r_cons_printf ("file: %s\nline: %d\n", file, line);
		line_old = line;
		if (line >= 2) {
			line -= 2;
		}
		if (r_file_exists (file)) {
			for (i = 0; i < 5; i++) {
				char *row = r_file_slurp_line (file, line + i, 0);
				if (row) {
					r_cons_printf ("%c %.3x  %s\n", line+i == line_old ? '>' : ' ', line+i, row);
					free (row);
				}
			}
		} else {
			eprintf ("Cannot open '%s'\n", file);
		}
	}
	return ret;
}