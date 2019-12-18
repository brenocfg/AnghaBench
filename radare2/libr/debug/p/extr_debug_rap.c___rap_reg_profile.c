#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  io; } ;
struct TYPE_5__ {TYPE_1__ iob; } ;
typedef  TYPE_2__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_cons_pipe_close (int) ; 
 int r_cons_pipe_open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_file_rm (char*) ; 
 char* r_file_slurp (char*,int /*<<< orphan*/ *) ; 
 char* r_file_temp (char*) ; 
 int /*<<< orphan*/  r_io_system (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *__rap_reg_profile(RDebug *dbg) {
	char *out, *tf = r_file_temp ("rap.XXXXXX");
	int fd = r_cons_pipe_open (tf, 1, 0);
	r_io_system (dbg->iob.io, "drp");
	r_cons_flush ();
	r_cons_pipe_close (fd);
	out = r_file_slurp (tf, NULL);
	r_file_rm (tf);
	free (tf);
	return out;
}