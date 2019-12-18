#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ objectSubId; scalar_t__ objectId; int /*<<< orphan*/  classId; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CurrentExtensionObject ; 
 int /*<<< orphan*/  DEPENDENCY_EXTENSION ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExtensionRelationId ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ creating_extension ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getExtensionOfObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  getObjectDescription (TYPE_1__ const*) ; 
 int /*<<< orphan*/  get_extension_name (scalar_t__) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__ const*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
recordDependencyOnCurrentExtension(const ObjectAddress *object,
								   bool isReplace)
{
	/* Only whole objects can be extension members */
	Assert(object->objectSubId == 0);

	if (creating_extension)
	{
		ObjectAddress extension;

		/* Only need to check for existing membership if isReplace */
		if (isReplace)
		{
			Oid			oldext;

			oldext = getExtensionOfObject(object->classId, object->objectId);
			if (OidIsValid(oldext))
			{
				/* If already a member of this extension, nothing to do */
				if (oldext == CurrentExtensionObject)
					return;
				/* Already a member of some other extension, so reject */
				ereport(ERROR,
						(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						 errmsg("%s is already a member of extension \"%s\"",
								getObjectDescription(object),
								get_extension_name(oldext))));
			}
		}

		/* OK, record it as a member of CurrentExtensionObject */
		extension.classId = ExtensionRelationId;
		extension.objectId = CurrentExtensionObject;
		extension.objectSubId = 0;

		recordDependencyOn(object, &extension, DEPENDENCY_EXTENSION);
	}
}