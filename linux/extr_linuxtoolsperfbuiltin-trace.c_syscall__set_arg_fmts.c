#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct syscall {TYPE_3__* arg_fmt; TYPE_2__* fmt; struct format_field* args; } ;
struct format_field {int flags; scalar_t__ name; scalar_t__ type; struct format_field* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  scnprintf; } ;
struct TYPE_5__ {TYPE_1__* arg; } ;
struct TYPE_4__ {scalar_t__ scnprintf; } ;

/* Variables and functions */
 int FIELD_IS_POINTER ; 
 int /*<<< orphan*/  SCA_FD ; 
 int /*<<< orphan*/  SCA_FILENAME ; 
 int /*<<< orphan*/  SCA_MODE_T ; 
 int /*<<< orphan*/  SCA_PID ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  syscall_arg__scnprintf_hex ; 

__attribute__((used)) static int syscall__set_arg_fmts(struct syscall *sc)
{
	struct format_field *field;
	int idx = 0, len;

	for (field = sc->args; field; field = field->next, ++idx) {
		if (sc->fmt && sc->fmt->arg[idx].scnprintf)
			continue;

		if (strcmp(field->type, "const char *") == 0 &&
			 (strcmp(field->name, "filename") == 0 ||
			  strcmp(field->name, "path") == 0 ||
			  strcmp(field->name, "pathname") == 0))
			sc->arg_fmt[idx].scnprintf = SCA_FILENAME;
		else if (field->flags & FIELD_IS_POINTER)
			sc->arg_fmt[idx].scnprintf = syscall_arg__scnprintf_hex;
		else if (strcmp(field->type, "pid_t") == 0)
			sc->arg_fmt[idx].scnprintf = SCA_PID;
		else if (strcmp(field->type, "umode_t") == 0)
			sc->arg_fmt[idx].scnprintf = SCA_MODE_T;
		else if ((strcmp(field->type, "int") == 0 ||
			  strcmp(field->type, "unsigned int") == 0 ||
			  strcmp(field->type, "long") == 0) &&
			 (len = strlen(field->name)) >= 2 &&
			 strcmp(field->name + len - 2, "fd") == 0) {
			/*
			 * /sys/kernel/tracing/events/syscalls/sys_enter*
			 * egrep 'field:.*fd;' .../format|sed -r 's/.*field:([a-z ]+) [a-z_]*fd.+/\1/g'|sort|uniq -c
			 * 65 int
			 * 23 unsigned int
			 * 7 unsigned long
			 */
			sc->arg_fmt[idx].scnprintf = SCA_FD;
		}
	}

	return 0;
}