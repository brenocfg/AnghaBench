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
struct line_range {char* file; char* function; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_c_func_name (char*) ; 
 int parse_line_num (char**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  semantic_error (char*,...) ; 
 char* strchr (char*,char) ; 
 void* strdup (char const*) ; 

int parse_line_range_desc(const char *arg, struct line_range *lr)
{
	char *range, *file, *name = strdup(arg);
	int err;

	if (!name)
		return -ENOMEM;

	lr->start = 0;
	lr->end = INT_MAX;

	range = strchr(name, ':');
	if (range) {
		*range++ = '\0';

		err = parse_line_num(&range, &lr->start, "start line");
		if (err)
			goto err;

		if (*range == '+' || *range == '-') {
			const char c = *range++;

			err = parse_line_num(&range, &lr->end, "end line");
			if (err)
				goto err;

			if (c == '+') {
				lr->end += lr->start;
				/*
				 * Adjust the number of lines here.
				 * If the number of lines == 1, the
				 * the end of line should be equal to
				 * the start of line.
				 */
				lr->end--;
			}
		}

		pr_debug("Line range is %d to %d\n", lr->start, lr->end);

		err = -EINVAL;
		if (lr->start > lr->end) {
			semantic_error("Start line must be smaller"
				       " than end line.\n");
			goto err;
		}
		if (*range != '\0') {
			semantic_error("Tailing with invalid str '%s'.\n", range);
			goto err;
		}
	}

	file = strchr(name, '@');
	if (file) {
		*file = '\0';
		lr->file = strdup(++file);
		if (lr->file == NULL) {
			err = -ENOMEM;
			goto err;
		}
		lr->function = name;
	} else if (strchr(name, '/') || strchr(name, '.'))
		lr->file = name;
	else if (is_c_func_name(name))/* We reuse it for checking funcname */
		lr->function = name;
	else {	/* Invalid name */
		semantic_error("'%s' is not a valid function name.\n", name);
		err = -EINVAL;
		goto err;
	}

	return 0;
err:
	free(name);
	return err;
}