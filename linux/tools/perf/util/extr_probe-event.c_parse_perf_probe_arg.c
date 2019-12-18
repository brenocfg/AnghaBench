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
struct perf_probe_arg_field {int ref; char* name; struct perf_probe_arg_field* next; int /*<<< orphan*/  index; } ;
struct perf_probe_arg {int user_access; char* var; int /*<<< orphan*/ * name; struct perf_probe_arg_field* field; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  is_c_varname (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  semantic_error (char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 void* strndup (char*,int) ; 
 char* strpbrk (char*,char*) ; 
 int /*<<< orphan*/  strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_access_is_supported () ; 
 struct perf_probe_arg_field* zalloc (int) ; 

__attribute__((used)) static int parse_perf_probe_arg(char *str, struct perf_probe_arg *arg)
{
	char *tmp, *goodname;
	struct perf_probe_arg_field **fieldp;

	pr_debug("parsing arg: %s into ", str);

	tmp = strchr(str, '=');
	if (tmp) {
		arg->name = strndup(str, tmp - str);
		if (arg->name == NULL)
			return -ENOMEM;
		pr_debug("name:%s ", arg->name);
		str = tmp + 1;
	}

	tmp = strchr(str, '@');
	if (tmp && tmp != str && strcmp(tmp + 1, "user")) { /* user attr */
		if (!user_access_is_supported()) {
			semantic_error("ftrace does not support user access\n");
			return -EINVAL;
		}
		*tmp = '\0';
		arg->user_access = true;
		pr_debug("user_access ");
	}

	tmp = strchr(str, ':');
	if (tmp) {	/* Type setting */
		*tmp = '\0';
		arg->type = strdup(tmp + 1);
		if (arg->type == NULL)
			return -ENOMEM;
		pr_debug("type:%s ", arg->type);
	}

	tmp = strpbrk(str, "-.[");
	if (!is_c_varname(str) || !tmp) {
		/* A variable, register, symbol or special value */
		arg->var = strdup(str);
		if (arg->var == NULL)
			return -ENOMEM;
		pr_debug("%s\n", arg->var);
		return 0;
	}

	/* Structure fields or array element */
	arg->var = strndup(str, tmp - str);
	if (arg->var == NULL)
		return -ENOMEM;
	goodname = arg->var;
	pr_debug("%s, ", arg->var);
	fieldp = &arg->field;

	do {
		*fieldp = zalloc(sizeof(struct perf_probe_arg_field));
		if (*fieldp == NULL)
			return -ENOMEM;
		if (*tmp == '[') {	/* Array */
			str = tmp;
			(*fieldp)->index = strtol(str + 1, &tmp, 0);
			(*fieldp)->ref = true;
			if (*tmp != ']' || tmp == str + 1) {
				semantic_error("Array index must be a"
						" number.\n");
				return -EINVAL;
			}
			tmp++;
			if (*tmp == '\0')
				tmp = NULL;
		} else {		/* Structure */
			if (*tmp == '.') {
				str = tmp + 1;
				(*fieldp)->ref = false;
			} else if (tmp[1] == '>') {
				str = tmp + 2;
				(*fieldp)->ref = true;
			} else {
				semantic_error("Argument parse error: %s\n",
					       str);
				return -EINVAL;
			}
			tmp = strpbrk(str, "-.[");
		}
		if (tmp) {
			(*fieldp)->name = strndup(str, tmp - str);
			if ((*fieldp)->name == NULL)
				return -ENOMEM;
			if (*str != '[')
				goodname = (*fieldp)->name;
			pr_debug("%s(%d), ", (*fieldp)->name, (*fieldp)->ref);
			fieldp = &(*fieldp)->next;
		}
	} while (tmp);
	(*fieldp)->name = strdup(str);
	if ((*fieldp)->name == NULL)
		return -ENOMEM;
	if (*str != '[')
		goodname = (*fieldp)->name;
	pr_debug("%s(%d)\n", (*fieldp)->name, (*fieldp)->ref);

	/* If no name is specified, set the last field name (not array index)*/
	if (!arg->name) {
		arg->name = strdup(goodname);
		if (arg->name == NULL)
			return -ENOMEM;
	}
	return 0;
}