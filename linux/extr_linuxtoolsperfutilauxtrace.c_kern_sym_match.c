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
struct sym_args {scalar_t__ cnt; scalar_t__ idx; scalar_t__ selected; scalar_t__ global; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ isupper (char) ; 
 scalar_t__ kallsyms__is_function (char) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kern_sym_match(struct sym_args *args, const char *name, char type)
{
	/* A function with the same name, and global or the n'th found or any */
	return kallsyms__is_function(type) &&
	       !strcmp(name, args->name) &&
	       ((args->global && isupper(type)) ||
		(args->selected && ++(args->cnt) == args->idx) ||
		(!args->global && !args->selected));
}