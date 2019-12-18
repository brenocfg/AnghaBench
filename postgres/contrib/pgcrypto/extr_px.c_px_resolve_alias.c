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
struct TYPE_3__ {char const* name; int /*<<< orphan*/  alias; } ;
typedef  TYPE_1__ PX_Alias ;

/* Variables and functions */
 scalar_t__ pg_strcasecmp (int /*<<< orphan*/ ,char const*) ; 

const char *
px_resolve_alias(const PX_Alias *list, const char *name)
{
	while (list->name)
	{
		if (pg_strcasecmp(list->alias, name) == 0)
			return list->name;
		list++;
	}
	return name;
}