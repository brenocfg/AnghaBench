#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  io; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pj_a (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_print_disasm_json (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int r_num_math (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void cmd_pDj(RCore *core, const char *arg) {
	int bsize = r_num_math (core->num, arg);
	if (bsize < 0) {
		bsize = -bsize;
	}
	PJ *pj = pj_new ();
	if (!pj) {
		return;
	}
	pj_a (pj);
	ut8 *buf = malloc (bsize);
	if (buf) {
		r_io_read_at (core->io, core->offset, buf, bsize);
		r_core_print_disasm_json (core, core->offset, buf, bsize, 0, pj);
		free (buf);
	} else {
		eprintf ("cannot allocate %d byte(s)\n", bsize);
	}
	pj_end (pj);
	r_cons_printf ("%s", pj_string (pj));
	pj_free (pj);
}