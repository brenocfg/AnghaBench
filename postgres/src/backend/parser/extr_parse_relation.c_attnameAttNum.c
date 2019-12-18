#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  attisdropped; int /*<<< orphan*/  attname; } ;
struct TYPE_6__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  TYPE_2__* Form_pg_attribute ;

/* Variables and functions */
 int InvalidAttrNumber ; 
 int RelationGetNumberOfAttributes (TYPE_1__*) ; 
 TYPE_2__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ *,char const*) ; 
 int specialAttNum (char const*) ; 

int
attnameAttNum(Relation rd, const char *attname, bool sysColOK)
{
	int			i;

	for (i = 0; i < RelationGetNumberOfAttributes(rd); i++)
	{
		Form_pg_attribute att = TupleDescAttr(rd->rd_att, i);

		if (namestrcmp(&(att->attname), attname) == 0 && !att->attisdropped)
			return i + 1;
	}

	if (sysColOK)
	{
		if ((i = specialAttNum(attname)) != InvalidAttrNumber)
			return i;
	}

	/* on failure */
	return InvalidAttrNumber;
}