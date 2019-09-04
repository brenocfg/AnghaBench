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
 char* skip_spaces (char*) ; 
 char* strchr (char*,char) ; 
 char* strim (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

char *aa_split_fqname(char *fqname, char **ns_name)
{
	char *name = strim(fqname);

	*ns_name = NULL;
	if (name[0] == ':') {
		char *split = strchr(&name[1], ':');
		*ns_name = skip_spaces(&name[1]);
		if (split) {
			/* overwrite ':' with \0 */
			*split++ = 0;
			if (strncmp(split, "//", 2) == 0)
				split += 2;
			name = skip_spaces(split);
		} else
			/* a ns name without a following profile is allowed */
			name = NULL;
	}
	if (name && *name == 0)
		name = NULL;

	return name;
}