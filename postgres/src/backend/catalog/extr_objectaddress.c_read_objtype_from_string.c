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
struct TYPE_3__ {int tm_type; int /*<<< orphan*/  tm_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* ObjectTypeMap ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int lengthof (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
read_objtype_from_string(const char *objtype)
{
	int			i;

	for (i = 0; i < lengthof(ObjectTypeMap); i++)
	{
		if (strcmp(ObjectTypeMap[i].tm_name, objtype) == 0)
			return ObjectTypeMap[i].tm_type;
	}
	ereport(ERROR,
			(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
			 errmsg("unrecognized object type \"%s\"", objtype)));

	return -1;					/* keep compiler quiet */
}