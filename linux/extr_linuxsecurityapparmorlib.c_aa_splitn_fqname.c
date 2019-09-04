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
 char* skipn_spaces (char const*,int) ; 
 char* strnchr (char const*,int,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

const char *aa_splitn_fqname(const char *fqname, size_t n, const char **ns_name,
			     size_t *ns_len)
{
	const char *end = fqname + n;
	const char *name = skipn_spaces(fqname, n);

	*ns_name = NULL;
	*ns_len = 0;

	if (!name)
		return NULL;

	if (name[0] == ':') {
		char *split = strnchr(&name[1], end - &name[1], ':');
		*ns_name = skipn_spaces(&name[1], end - &name[1]);
		if (!*ns_name)
			return NULL;
		if (split) {
			*ns_len = split - *ns_name;
			if (*ns_len == 0)
				*ns_name = NULL;
			split++;
			if (end - split > 1 && strncmp(split, "//", 2) == 0)
				split += 2;
			name = skipn_spaces(split, end - split);
		} else {
			/* a ns name without a following profile is allowed */
			name = NULL;
			*ns_len = end - *ns_name;
		}
	}
	if (name && *name == 0)
		name = NULL;

	return name;
}