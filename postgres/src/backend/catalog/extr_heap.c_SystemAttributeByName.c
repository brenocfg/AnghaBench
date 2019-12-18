#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  attname; } ;
typedef  TYPE_1__ FormData_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_1__** SysAtt ; 
 scalar_t__ lengthof (TYPE_1__**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

const FormData_pg_attribute *
SystemAttributeByName(const char *attname)
{
	int			j;

	for (j = 0; j < (int) lengthof(SysAtt); j++)
	{
		const FormData_pg_attribute *att = SysAtt[j];

		if (strcmp(NameStr(att->attname), attname) == 0)
			return att;
	}

	return NULL;
}