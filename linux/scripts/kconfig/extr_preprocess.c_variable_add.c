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
struct variable {int flavor; char* value; int /*<<< orphan*/  node; scalar_t__ exp_count; void* name; } ;
typedef  enum variable_flavor { ____Placeholder_variable_flavor } variable_flavor ;

/* Variables and functions */
 int VAR_APPEND ; 
 int VAR_RECURSIVE ; 
 int VAR_SIMPLE ; 
 char* expand_string (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  variable_list ; 
 struct variable* variable_lookup (char const*) ; 
 struct variable* xmalloc (int) ; 
 char* xrealloc (char*,scalar_t__) ; 
 void* xstrdup (char const*) ; 

void variable_add(const char *name, const char *value,
		  enum variable_flavor flavor)
{
	struct variable *v;
	char *new_value;
	bool append = false;

	v = variable_lookup(name);
	if (v) {
		/* For defined variables, += inherits the existing flavor */
		if (flavor == VAR_APPEND) {
			flavor = v->flavor;
			append = true;
		} else {
			free(v->value);
		}
	} else {
		/* For undefined variables, += assumes the recursive flavor */
		if (flavor == VAR_APPEND)
			flavor = VAR_RECURSIVE;

		v = xmalloc(sizeof(*v));
		v->name = xstrdup(name);
		v->exp_count = 0;
		list_add_tail(&v->node, &variable_list);
	}

	v->flavor = flavor;

	if (flavor == VAR_SIMPLE)
		new_value = expand_string(value);
	else
		new_value = xstrdup(value);

	if (append) {
		v->value = xrealloc(v->value,
				    strlen(v->value) + strlen(new_value) + 2);
		strcat(v->value, " ");
		strcat(v->value, new_value);
		free(new_value);
	} else {
		v->value = new_value;
	}
}