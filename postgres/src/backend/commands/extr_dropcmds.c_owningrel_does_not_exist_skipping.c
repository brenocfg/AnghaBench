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
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 char* NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* gettext_noop (char*) ; 
 int /*<<< orphan*/  list_copy (int /*<<< orphan*/ *) ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_truncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * makeRangeVarFromNameList (int /*<<< orphan*/ *) ; 
 scalar_t__ schema_does_not_exist_skipping (int /*<<< orphan*/ *,char const**,char**) ; 

__attribute__((used)) static bool
owningrel_does_not_exist_skipping(List *object, const char **msg, char **name)
{
	List	   *parent_object;
	RangeVar   *parent_rel;

	parent_object = list_truncate(list_copy(object),
								  list_length(object) - 1);

	if (schema_does_not_exist_skipping(parent_object, msg, name))
		return true;

	parent_rel = makeRangeVarFromNameList(parent_object);

	if (!OidIsValid(RangeVarGetRelid(parent_rel, NoLock, true)))
	{
		*msg = gettext_noop("relation \"%s\" does not exist, skipping");
		*name = NameListToString(parent_object);

		return true;
	}

	return false;
}