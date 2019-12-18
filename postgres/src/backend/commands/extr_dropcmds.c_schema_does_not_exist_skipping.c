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
struct TYPE_3__ {char* schemaname; } ;
typedef  TYPE_1__ RangeVar ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  LookupNamespaceNoError (char*) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 char* gettext_noop (char*) ; 
 TYPE_1__* makeRangeVarFromNameList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
schema_does_not_exist_skipping(List *object, const char **msg, char **name)
{
	RangeVar   *rel;

	rel = makeRangeVarFromNameList(object);

	if (rel->schemaname != NULL &&
		!OidIsValid(LookupNamespaceNoError(rel->schemaname)))
	{
		*msg = gettext_noop("schema \"%s\" does not exist, skipping");
		*name = rel->schemaname;

		return true;
	}

	return false;
}