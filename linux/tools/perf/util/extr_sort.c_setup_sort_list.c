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
struct perf_hpp_list {int dummy; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  cacheline_size () ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int sort_dimension__add (struct perf_hpp_list*,char*,struct evlist*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static int setup_sort_list(struct perf_hpp_list *list, char *str,
			   struct evlist *evlist)
{
	char *tmp, *tok;
	int ret = 0;
	int level = 0;
	int next_level = 1;
	bool in_group = false;

	do {
		tok = str;
		tmp = strpbrk(str, "{}, ");
		if (tmp) {
			if (in_group)
				next_level = level;
			else
				next_level = level + 1;

			if (*tmp == '{')
				in_group = true;
			else if (*tmp == '}')
				in_group = false;

			*tmp = '\0';
			str = tmp + 1;
		}

		if (*tok) {
			ret = sort_dimension__add(list, tok, evlist, level);
			if (ret == -EINVAL) {
				if (!cacheline_size() && !strncasecmp(tok, "dcacheline", strlen(tok)))
					pr_err("The \"dcacheline\" --sort key needs to know the cacheline size and it couldn't be determined on this system");
				else
					pr_err("Invalid --sort key: `%s'", tok);
				break;
			} else if (ret == -ESRCH) {
				pr_err("Unknown --sort key: `%s'", tok);
				break;
			}
		}

		level = next_level;
	} while (tmp);

	return ret;
}