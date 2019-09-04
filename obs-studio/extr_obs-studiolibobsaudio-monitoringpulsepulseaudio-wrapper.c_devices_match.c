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
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  get_default_id (char**) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

bool devices_match(const char *id1, const char *id2)
{
	bool match;
	char *name1 = NULL;
	char *name2 = NULL;

	if (!id1 || !id2)
		return false;

	if (strcmp(id1, "default") == 0) {
		get_default_id(&name1);
		id1 = name1;
	}
	if (strcmp(id2, "default") == 0) {
		get_default_id(&name2);
		id2 = name2;
	}

	match = strcmp(id1, id2) == 0;
	bfree(name1);
	bfree(name2);
	return match;
}