#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tmplinit; int /*<<< orphan*/  tmpllexize; int /*<<< orphan*/  tmplnamespace; int /*<<< orphan*/  oid; } ;
struct TYPE_7__ {int /*<<< orphan*/  objectId; scalar_t__ objectSubId; int /*<<< orphan*/  classId; } ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_ts_template ;

/* Variables and functions */
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  TSTemplateRelationId ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_1__*,int) ; 

__attribute__((used)) static ObjectAddress
makeTSTemplateDependencies(HeapTuple tuple)
{
	Form_pg_ts_template tmpl = (Form_pg_ts_template) GETSTRUCT(tuple);
	ObjectAddress myself,
				referenced;

	myself.classId = TSTemplateRelationId;
	myself.objectId = tmpl->oid;
	myself.objectSubId = 0;

	/* dependency on namespace */
	referenced.classId = NamespaceRelationId;
	referenced.objectId = tmpl->tmplnamespace;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	/* dependency on extension */
	recordDependencyOnCurrentExtension(&myself, false);

	/* dependencies on functions */
	referenced.classId = ProcedureRelationId;
	referenced.objectSubId = 0;

	referenced.objectId = tmpl->tmpllexize;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	if (OidIsValid(tmpl->tmplinit))
	{
		referenced.objectId = tmpl->tmplinit;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}

	return myself;
}