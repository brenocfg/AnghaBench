#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  prop; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  IndexAMProperty ;

/* Variables and functions */
 int /*<<< orphan*/  AMPROP_UNKNOWN ; 
 TYPE_1__* am_propnames ; 
 int lengthof (TYPE_1__*) ; 
 scalar_t__ pg_strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static IndexAMProperty
lookup_prop_name(const char *name)
{
	int			i;

	for (i = 0; i < lengthof(am_propnames); i++)
	{
		if (pg_strcasecmp(am_propnames[i].name, name) == 0)
			return am_propnames[i].prop;
	}

	/* We do not throw an error, so that AMs can define their own properties */
	return AMPROP_UNKNOWN;
}