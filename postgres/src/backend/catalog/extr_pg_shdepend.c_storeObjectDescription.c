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
struct TYPE_5__ {scalar_t__ len; } ;
typedef  TYPE_1__* StringInfo ;
typedef  scalar_t__ SharedDependencyType ;
typedef  int SharedDependencyObjectType ;
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  LOCAL_OBJECT 130 
#define  REMOTE_OBJECT 129 
 scalar_t__ SHARED_DEPENDENCY_ACL ; 
 scalar_t__ SHARED_DEPENDENCY_OWNER ; 
 scalar_t__ SHARED_DEPENDENCY_POLICY ; 
#define  SHARED_OBJECT 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 char* getObjectDescription (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngettext (char*,char*,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static void
storeObjectDescription(StringInfo descs,
					   SharedDependencyObjectType type,
					   ObjectAddress *object,
					   SharedDependencyType deptype,
					   int count)
{
	char	   *objdesc = getObjectDescription(object);

	/* separate entries with a newline */
	if (descs->len != 0)
		appendStringInfoChar(descs, '\n');

	switch (type)
	{
		case LOCAL_OBJECT:
		case SHARED_OBJECT:
			if (deptype == SHARED_DEPENDENCY_OWNER)
				appendStringInfo(descs, _("owner of %s"), objdesc);
			else if (deptype == SHARED_DEPENDENCY_ACL)
				appendStringInfo(descs, _("privileges for %s"), objdesc);
			else if (deptype == SHARED_DEPENDENCY_POLICY)
				appendStringInfo(descs, _("target of %s"), objdesc);
			else
				elog(ERROR, "unrecognized dependency type: %d",
					 (int) deptype);
			break;

		case REMOTE_OBJECT:
			/* translator: %s will always be "database %s" */
			appendStringInfo(descs, ngettext("%d object in %s",
											 "%d objects in %s",
											 count),
							 count, objdesc);
			break;

		default:
			elog(ERROR, "unrecognized object type: %d", type);
	}

	pfree(objdesc);
}