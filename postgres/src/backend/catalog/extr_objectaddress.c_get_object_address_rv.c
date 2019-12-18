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
struct TYPE_3__ {scalar_t__ catalogname; scalar_t__ schemaname; scalar_t__ relname; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ RangeVar ;
typedef  int /*<<< orphan*/  ObjectType ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  get_object_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * lcons (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeString (scalar_t__) ; 

ObjectAddress
get_object_address_rv(ObjectType objtype, RangeVar *rel, List *object,
					  Relation *relp, LOCKMODE lockmode,
					  bool missing_ok)
{
	if (rel)
	{
		object = lcons(makeString(rel->relname), object);
		if (rel->schemaname)
			object = lcons(makeString(rel->schemaname), object);
		if (rel->catalogname)
			object = lcons(makeString(rel->catalogname), object);
	}

	return get_object_address(objtype, (Node *) object,
							  relp, lockmode, missing_ok);
}