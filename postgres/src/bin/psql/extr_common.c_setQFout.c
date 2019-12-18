#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int queryFoutPipe; int /*<<< orphan*/ * queryFout; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openQueryOutputFile (char const*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  restore_sigpipe_trap () ; 
 int /*<<< orphan*/  set_sigpipe_trap_state (int) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

bool
setQFout(const char *fname)
{
	FILE	   *fout;
	bool		is_pipe;

	/* First make sure we can open the new output file/pipe */
	if (!openQueryOutputFile(fname, &fout, &is_pipe))
		return false;

	/* Close old file/pipe */
	if (pset.queryFout && pset.queryFout != stdout && pset.queryFout != stderr)
	{
		if (pset.queryFoutPipe)
			pclose(pset.queryFout);
		else
			fclose(pset.queryFout);
	}

	pset.queryFout = fout;
	pset.queryFoutPipe = is_pipe;

	/* Adjust SIGPIPE handling appropriately: ignore signal if is_pipe */
	set_sigpipe_trap_state(is_pipe);
	restore_sigpipe_trap();

	return true;
}