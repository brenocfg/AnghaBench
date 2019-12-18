#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hist_field {int flags; } ;

/* Variables and functions */
 int HIST_FIELD_FL_EXECNAME ; 
 int HIST_FIELD_FL_HEX ; 
 int HIST_FIELD_FL_LOG2 ; 
 int HIST_FIELD_FL_SYM ; 
 int HIST_FIELD_FL_SYM_OFFSET ; 
 int HIST_FIELD_FL_SYSCALL ; 
 int HIST_FIELD_FL_TIMESTAMP_USECS ; 

__attribute__((used)) static const char *get_hist_field_flags(struct hist_field *hist_field)
{
	const char *flags_str = NULL;

	if (hist_field->flags & HIST_FIELD_FL_HEX)
		flags_str = "hex";
	else if (hist_field->flags & HIST_FIELD_FL_SYM)
		flags_str = "sym";
	else if (hist_field->flags & HIST_FIELD_FL_SYM_OFFSET)
		flags_str = "sym-offset";
	else if (hist_field->flags & HIST_FIELD_FL_EXECNAME)
		flags_str = "execname";
	else if (hist_field->flags & HIST_FIELD_FL_SYSCALL)
		flags_str = "syscall";
	else if (hist_field->flags & HIST_FIELD_FL_LOG2)
		flags_str = "log2";
	else if (hist_field->flags & HIST_FIELD_FL_TIMESTAMP_USECS)
		flags_str = "usecs";

	return flags_str;
}