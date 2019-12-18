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
struct TYPE_3__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  ObjectAddresses ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 void* AlterObjectNamespace_internal (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  AlterTableNamespaceInternal (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ *) ; 
 void* AlterTypeNamespace_oid (void*,void*,int /*<<< orphan*/ *) ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  NoLock ; 
#define  OCLASS_AM 165 
#define  OCLASS_AMOP 164 
#define  OCLASS_AMPROC 163 
#define  OCLASS_CAST 162 
#define  OCLASS_CLASS 161 
#define  OCLASS_COLLATION 160 
#define  OCLASS_CONSTRAINT 159 
#define  OCLASS_CONVERSION 158 
#define  OCLASS_DATABASE 157 
#define  OCLASS_DEFACL 156 
#define  OCLASS_DEFAULT 155 
#define  OCLASS_EVENT_TRIGGER 154 
#define  OCLASS_EXTENSION 153 
#define  OCLASS_FDW 152 
#define  OCLASS_FOREIGN_SERVER 151 
#define  OCLASS_LANGUAGE 150 
#define  OCLASS_LARGEOBJECT 149 
#define  OCLASS_OPCLASS 148 
#define  OCLASS_OPERATOR 147 
#define  OCLASS_OPFAMILY 146 
#define  OCLASS_POLICY 145 
#define  OCLASS_PROC 144 
#define  OCLASS_PUBLICATION 143 
#define  OCLASS_PUBLICATION_REL 142 
#define  OCLASS_REWRITE 141 
#define  OCLASS_ROLE 140 
#define  OCLASS_SCHEMA 139 
#define  OCLASS_STATISTIC_EXT 138 
#define  OCLASS_SUBSCRIPTION 137 
#define  OCLASS_TBLSPACE 136 
#define  OCLASS_TRANSFORM 135 
#define  OCLASS_TRIGGER 134 
#define  OCLASS_TSCONFIG 133 
#define  OCLASS_TSDICT 132 
#define  OCLASS_TSPARSER 131 
#define  OCLASS_TSTEMPLATE 130 
#define  OCLASS_TYPE 129 
#define  OCLASS_USER_MAPPING 128 
 void* RelationGetNamespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int getObjectClass (TYPE_1__*) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (void*,int /*<<< orphan*/ ) ; 

Oid
AlterObjectNamespace_oid(Oid classId, Oid objid, Oid nspOid,
						 ObjectAddresses *objsMoved)
{
	Oid			oldNspOid = InvalidOid;
	ObjectAddress dep;

	dep.classId = classId;
	dep.objectId = objid;
	dep.objectSubId = 0;

	switch (getObjectClass(&dep))
	{
		case OCLASS_CLASS:
			{
				Relation	rel;

				rel = relation_open(objid, AccessExclusiveLock);
				oldNspOid = RelationGetNamespace(rel);

				AlterTableNamespaceInternal(rel, oldNspOid, nspOid, objsMoved);

				relation_close(rel, NoLock);
				break;
			}

		case OCLASS_TYPE:
			oldNspOid = AlterTypeNamespace_oid(objid, nspOid, objsMoved);
			break;

		case OCLASS_PROC:
		case OCLASS_COLLATION:
		case OCLASS_CONVERSION:
		case OCLASS_OPERATOR:
		case OCLASS_OPCLASS:
		case OCLASS_OPFAMILY:
		case OCLASS_STATISTIC_EXT:
		case OCLASS_TSPARSER:
		case OCLASS_TSDICT:
		case OCLASS_TSTEMPLATE:
		case OCLASS_TSCONFIG:
			{
				Relation	catalog;

				catalog = table_open(classId, RowExclusiveLock);

				oldNspOid = AlterObjectNamespace_internal(catalog, objid,
														  nspOid);

				table_close(catalog, RowExclusiveLock);
			}
			break;

		case OCLASS_CAST:
		case OCLASS_CONSTRAINT:
		case OCLASS_DEFAULT:
		case OCLASS_LANGUAGE:
		case OCLASS_LARGEOBJECT:
		case OCLASS_AM:
		case OCLASS_AMOP:
		case OCLASS_AMPROC:
		case OCLASS_REWRITE:
		case OCLASS_TRIGGER:
		case OCLASS_SCHEMA:
		case OCLASS_ROLE:
		case OCLASS_DATABASE:
		case OCLASS_TBLSPACE:
		case OCLASS_FDW:
		case OCLASS_FOREIGN_SERVER:
		case OCLASS_USER_MAPPING:
		case OCLASS_DEFACL:
		case OCLASS_EXTENSION:
		case OCLASS_EVENT_TRIGGER:
		case OCLASS_POLICY:
		case OCLASS_PUBLICATION:
		case OCLASS_PUBLICATION_REL:
		case OCLASS_SUBSCRIPTION:
		case OCLASS_TRANSFORM:
			/* ignore object types that don't have schema-qualified names */
			break;

			/*
			 * There's intentionally no default: case here; we want the
			 * compiler to warn if a new OCLASS hasn't been handled above.
			 */
	}

	return oldNspOid;
}