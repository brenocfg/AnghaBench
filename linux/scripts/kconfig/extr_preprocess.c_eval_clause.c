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

/* Variables and functions */
 int FUNCTION_MAX_ARGS ; 
 char* env_expand (char*) ; 
 char* expand_string_with_args (char*,int,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* function_expand (char*,int,char**) ; 
 int /*<<< orphan*/  pperror (char*) ; 
 unsigned long strtoul (char*,char**,int) ; 
 char* variable_expand (char*,int,char**) ; 
 char* xstrdup (char*) ; 
 char* xstrndup (char const*,size_t) ; 

__attribute__((used)) static char *eval_clause(const char *str, size_t len, int argc, char *argv[])
{
	char *tmp, *name, *res, *endptr, *prev, *p;
	int new_argc = 0;
	char *new_argv[FUNCTION_MAX_ARGS];
	int nest = 0;
	int i;
	unsigned long n;

	tmp = xstrndup(str, len);

	/*
	 * If variable name is '1', '2', etc.  It is generally an argument
	 * from a user-function call (i.e. local-scope variable).  If not
	 * available, then look-up global-scope variables.
	 */
	n = strtoul(tmp, &endptr, 10);
	if (!*endptr && n > 0 && n <= argc) {
		res = xstrdup(argv[n - 1]);
		goto free_tmp;
	}

	prev = p = tmp;

	/*
	 * Split into tokens
	 * The function name and arguments are separated by a comma.
	 * For example, if the function call is like this:
	 *   $(foo,$(x),$(y))
	 *
	 * The input string for this helper should be:
	 *   foo,$(x),$(y)
	 *
	 * and split into:
	 *   new_argv[0] = 'foo'
	 *   new_argv[1] = '$(x)'
	 *   new_argv[2] = '$(y)'
	 */
	while (*p) {
		if (nest == 0 && *p == ',') {
			*p = 0;
			if (new_argc >= FUNCTION_MAX_ARGS)
				pperror("too many function arguments");
			new_argv[new_argc++] = prev;
			prev = p + 1;
		} else if (*p == '(') {
			nest++;
		} else if (*p == ')') {
			nest--;
		}

		p++;
	}
	new_argv[new_argc++] = prev;

	/*
	 * Shift arguments
	 * new_argv[0] represents a function name or a variable name.  Put it
	 * into 'name', then shift the rest of the arguments.  This simplifies
	 * 'const' handling.
	 */
	name = expand_string_with_args(new_argv[0], argc, argv);
	new_argc--;
	for (i = 0; i < new_argc; i++)
		new_argv[i] = expand_string_with_args(new_argv[i + 1],
						      argc, argv);

	/* Search for variables */
	res = variable_expand(name, new_argc, new_argv);
	if (res)
		goto free;

	/* Look for built-in functions */
	res = function_expand(name, new_argc, new_argv);
	if (res)
		goto free;

	/* Last, try environment variable */
	if (new_argc == 0) {
		res = env_expand(name);
		if (res)
			goto free;
	}

	res = xstrdup("");
free:
	for (i = 0; i < new_argc; i++)
		free(new_argv[i]);
	free(name);
free_tmp:
	free(tmp);

	return res;
}