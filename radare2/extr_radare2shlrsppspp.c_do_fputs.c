#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ifl; int /*<<< orphan*/ * echo; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* fputs ) (TYPE_2__*,char*) ;TYPE_1__ state; } ;
struct TYPE_7__ {scalar_t__ fout; } ;
typedef  TYPE_2__ Output ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 TYPE_4__* proc ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*) ; 

int do_fputs(Output *out, char *str) {
	int i;
	int printed = 0;
	for (i = 0; i <= proc->state.ifl; i++) {
		if (!proc->state.echo[i]) {
			return printed;
		}
	}
	if (str[0]) {
		printed = 1;
	}
	if (proc->fputs) {
		proc->fputs (out, str);
	} else {
		if (out->fout) {
			fprintf (out->fout, "%s", str);
		}
	}
	return printed;
}