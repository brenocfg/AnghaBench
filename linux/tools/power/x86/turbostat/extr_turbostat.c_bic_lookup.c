#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum show_hide_mode { ____Placeholder_show_hide_mode } show_hide_mode ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int MAX_BIC ; 
 int MAX_DEFERRED ; 
 int SHOW_LIST ; 
 TYPE_1__* bic ; 
 scalar_t__ debug ; 
 int deferred_skip_index ; 
 char** deferred_skip_names ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

unsigned long long bic_lookup(char *name_list, enum show_hide_mode mode)
{
	int i;
	unsigned long long retval = 0;

	while (name_list) {
		char *comma;

		comma = strchr(name_list, ',');

		if (comma)
			*comma = '\0';

		if (!strcmp(name_list, "all"))
			return ~0;

		for (i = 0; i < MAX_BIC; ++i) {
			if (!strcmp(name_list, bic[i].name)) {
				retval |= (1ULL << i);
				break;
			}
		}
		if (i == MAX_BIC) {
			if (mode == SHOW_LIST) {
				fprintf(stderr, "Invalid counter name: %s\n", name_list);
				exit(-1);
			}
			deferred_skip_names[deferred_skip_index++] = name_list;
			if (debug)
				fprintf(stderr, "deferred \"%s\"\n", name_list);
			if (deferred_skip_index >= MAX_DEFERRED) {
				fprintf(stderr, "More than max %d un-recognized --skip options '%s'\n",
					MAX_DEFERRED, name_list);
				help();
				exit(1);
			}
		}

		name_list = comma;
		if (name_list)
			name_list++;

	}
	return retval;
}