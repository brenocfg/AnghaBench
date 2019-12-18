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
struct syscall {int nr_args; TYPE_1__* fmt; int /*<<< orphan*/ * arg_fmt; } ;
struct TYPE_2__ {int nr_args; int /*<<< orphan*/ * arg; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 

__attribute__((used)) static int syscall__alloc_arg_fmts(struct syscall *sc, int nr_args)
{
	int idx;

	if (nr_args == 6 && sc->fmt && sc->fmt->nr_args != 0)
		nr_args = sc->fmt->nr_args;

	sc->arg_fmt = calloc(nr_args, sizeof(*sc->arg_fmt));
	if (sc->arg_fmt == NULL)
		return -1;

	for (idx = 0; idx < nr_args; ++idx) {
		if (sc->fmt)
			sc->arg_fmt[idx] = sc->fmt->arg[idx];
	}

	sc->nr_args = nr_args;
	return 0;
}