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
struct ftrace_branch_data {char* file; } ;

/* Variables and functions */
 int strlen (char*) ; 

__attribute__((used)) static const char *branch_stat_process_file(struct ftrace_branch_data *p)
{
	const char *f;

	/* Only print the file, not the path */
	f = p->file + strlen(p->file);
	while (f >= p->file && *f != '/')
		f--;
	return ++f;
}