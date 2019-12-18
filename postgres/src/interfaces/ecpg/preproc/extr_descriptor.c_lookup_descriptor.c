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
struct descriptor {scalar_t__ connection; scalar_t__ name; struct descriptor* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_WARNING ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 struct descriptor* descriptors ; 
 int /*<<< orphan*/  mmerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 

struct descriptor
		   *
lookup_descriptor(char *name, char *connection)
{
	struct descriptor *i;

	if (name[0] != '"')
		return NULL;

	for (i = descriptors; i; i = i->next)
	{
		if (strcmp(name, i->name) == 0)
		{
			if ((!connection && !i->connection)
				|| (connection && i->connection
					&& strcmp(connection, i->connection) == 0))
				return i;
		}
	}
	mmerror(PARSE_ERROR, ET_WARNING, "descriptor \"%s\" does not exist", name);
	return NULL;
}