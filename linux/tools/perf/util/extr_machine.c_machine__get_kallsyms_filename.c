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
struct machine {int /*<<< orphan*/  root_dir; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_guest_kallsyms; } ;

/* Variables and functions */
 scalar_t__ machine__is_default_guest (struct machine*) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ symbol_conf ; 

void machine__get_kallsyms_filename(struct machine *machine, char *buf,
				    size_t bufsz)
{
	if (machine__is_default_guest(machine))
		scnprintf(buf, bufsz, "%s", symbol_conf.default_guest_kallsyms);
	else
		scnprintf(buf, bufsz, "%s/proc/kallsyms", machine->root_dir);
}