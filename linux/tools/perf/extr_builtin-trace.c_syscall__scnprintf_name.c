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
struct syscall_arg {size_t idx; } ;
struct syscall {TYPE_1__* arg_fmt; } ;
struct TYPE_2__ {size_t name; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*,size_t) ; 

__attribute__((used)) static size_t syscall__scnprintf_name(struct syscall *sc, char *bf, size_t size,
				      struct syscall_arg *arg)
{
	if (sc->arg_fmt && sc->arg_fmt[arg->idx].name)
		return scnprintf(bf, size, "%s: ", sc->arg_fmt[arg->idx].name);

	return scnprintf(bf, size, "arg%d: ", arg->idx);
}