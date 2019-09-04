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
 int asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prog ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  topic ; 

__attribute__((used)) static char *get_topic(void)
{
	char *tp;
	int i;

	/* tp is free'd in process_one_file() */
	i = asprintf(&tp, "%s", topic);
	if (i < 0) {
		pr_info("%s: asprintf() error %s\n", prog);
		return NULL;
	}

	for (i = 0; i < (int) strlen(tp); i++) {
		char c = tp[i];

		if (c == '-')
			tp[i] = ' ';
		else if (c == '.') {
			tp[i] = '\0';
			break;
		}
	}

	return tp;
}