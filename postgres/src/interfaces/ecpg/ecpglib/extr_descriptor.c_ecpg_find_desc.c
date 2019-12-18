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
struct descriptor {int /*<<< orphan*/  name; struct descriptor* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_SQLSTATE_INVALID_SQL_DESCRIPTOR_NAME ; 
 int /*<<< orphan*/  ECPG_UNKNOWN_DESCRIPTOR ; 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 struct descriptor* get_descriptors () ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

struct descriptor *
ecpg_find_desc(int line, const char *name)
{
	struct descriptor *desc;

	for (desc = get_descriptors(); desc; desc = desc->next)
	{
		if (strcmp(name, desc->name) == 0)
			return desc;
	}

	ecpg_raise(line, ECPG_UNKNOWN_DESCRIPTOR, ECPG_SQLSTATE_INVALID_SQL_DESCRIPTOR_NAME, name);
	return NULL;				/* not found */
}