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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ match_last_lsm (char*,char const*) ; 

__attribute__((used)) static int lsm_append(const char *new, char **result)
{
	char *cp;

	if (*result == NULL) {
		*result = kstrdup(new, GFP_KERNEL);
		if (*result == NULL)
			return -ENOMEM;
	} else {
		/* Check if it is the last registered name */
		if (match_last_lsm(*result, new))
			return 0;
		cp = kasprintf(GFP_KERNEL, "%s,%s", *result, new);
		if (cp == NULL)
			return -ENOMEM;
		kfree(*result);
		*result = cp;
	}
	return 0;
}