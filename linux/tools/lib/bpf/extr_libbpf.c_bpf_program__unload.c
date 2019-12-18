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
struct TYPE_2__ {int nr; int /*<<< orphan*/ * fds; } ;
struct bpf_program {int /*<<< orphan*/ * line_info; int /*<<< orphan*/ * func_info; TYPE_1__ instances; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int /*<<< orphan*/  zclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

void bpf_program__unload(struct bpf_program *prog)
{
	int i;

	if (!prog)
		return;

	/*
	 * If the object is opened but the program was never loaded,
	 * it is possible that prog->instances.nr == -1.
	 */
	if (prog->instances.nr > 0) {
		for (i = 0; i < prog->instances.nr; i++)
			zclose(prog->instances.fds[i]);
	} else if (prog->instances.nr != -1) {
		pr_warning("Internal error: instances.nr is %d\n",
			   prog->instances.nr);
	}

	prog->instances.nr = -1;
	zfree(&prog->instances.fds);

	zfree(&prog->func_info);
	zfree(&prog->line_info);
}