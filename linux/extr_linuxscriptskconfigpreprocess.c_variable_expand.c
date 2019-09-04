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
struct variable {int exp_count; scalar_t__ flavor; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ VAR_RECURSIVE ; 
 char* expand_string_with_args (int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  pperror (char*,...) ; 
 struct variable* variable_lookup (char const*) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *variable_expand(const char *name, int argc, char *argv[])
{
	struct variable *v;
	char *res;

	v = variable_lookup(name);
	if (!v)
		return NULL;

	if (argc == 0 && v->exp_count)
		pperror("Recursive variable '%s' references itself (eventually)",
			name);

	if (v->exp_count > 1000)
		pperror("Too deep recursive expansion");

	v->exp_count++;

	if (v->flavor == VAR_RECURSIVE)
		res = expand_string_with_args(v->value, argc, argv);
	else
		res = xstrdup(v->value);

	v->exp_count--;

	return res;
}