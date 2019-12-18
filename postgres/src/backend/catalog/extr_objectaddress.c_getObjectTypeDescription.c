#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  objectSubId; } ;
struct TYPE_10__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ ObjectAddress ;

/* Variables and functions */
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
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  getConstraintTypeDescription (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int getObjectClass (TYPE_2__ const*) ; 
 int /*<<< orphan*/  getProcedureTypeDescription (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getRelationTypeDescription (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

char *
getObjectTypeDescription(const ObjectAddress *object)
{
	StringInfoData buffer;

	initStringInfo(&buffer);

	switch (getObjectClass(object))
	{
		case OCLASS_CLASS:
			getRelationTypeDescription(&buffer, object->objectId,
									   object->objectSubId);
			break;

		case OCLASS_PROC:
			getProcedureTypeDescription(&buffer, object->objectId);
			break;

		case OCLASS_TYPE:
			appendStringInfoString(&buffer, "type");
			break;

		case OCLASS_CAST:
			appendStringInfoString(&buffer, "cast");
			break;

		case OCLASS_COLLATION:
			appendStringInfoString(&buffer, "collation");
			break;

		case OCLASS_CONSTRAINT:
			getConstraintTypeDescription(&buffer, object->objectId);
			break;

		case OCLASS_CONVERSION:
			appendStringInfoString(&buffer, "conversion");
			break;

		case OCLASS_DEFAULT:
			appendStringInfoString(&buffer, "default value");
			break;

		case OCLASS_LANGUAGE:
			appendStringInfoString(&buffer, "language");
			break;

		case OCLASS_LARGEOBJECT:
			appendStringInfoString(&buffer, "large object");
			break;

		case OCLASS_OPERATOR:
			appendStringInfoString(&buffer, "operator");
			break;

		case OCLASS_OPCLASS:
			appendStringInfoString(&buffer, "operator class");
			break;

		case OCLASS_OPFAMILY:
			appendStringInfoString(&buffer, "operator family");
			break;

		case OCLASS_AM:
			appendStringInfoString(&buffer, "access method");
			break;

		case OCLASS_AMOP:
			appendStringInfoString(&buffer, "operator of access method");
			break;

		case OCLASS_AMPROC:
			appendStringInfoString(&buffer, "function of access method");
			break;

		case OCLASS_REWRITE:
			appendStringInfoString(&buffer, "rule");
			break;

		case OCLASS_TRIGGER:
			appendStringInfoString(&buffer, "trigger");
			break;

		case OCLASS_SCHEMA:
			appendStringInfoString(&buffer, "schema");
			break;

		case OCLASS_STATISTIC_EXT:
			appendStringInfoString(&buffer, "statistics object");
			break;

		case OCLASS_TSPARSER:
			appendStringInfoString(&buffer, "text search parser");
			break;

		case OCLASS_TSDICT:
			appendStringInfoString(&buffer, "text search dictionary");
			break;

		case OCLASS_TSTEMPLATE:
			appendStringInfoString(&buffer, "text search template");
			break;

		case OCLASS_TSCONFIG:
			appendStringInfoString(&buffer, "text search configuration");
			break;

		case OCLASS_ROLE:
			appendStringInfoString(&buffer, "role");
			break;

		case OCLASS_DATABASE:
			appendStringInfoString(&buffer, "database");
			break;

		case OCLASS_TBLSPACE:
			appendStringInfoString(&buffer, "tablespace");
			break;

		case OCLASS_FDW:
			appendStringInfoString(&buffer, "foreign-data wrapper");
			break;

		case OCLASS_FOREIGN_SERVER:
			appendStringInfoString(&buffer, "server");
			break;

		case OCLASS_USER_MAPPING:
			appendStringInfoString(&buffer, "user mapping");
			break;

		case OCLASS_DEFACL:
			appendStringInfoString(&buffer, "default acl");
			break;

		case OCLASS_EXTENSION:
			appendStringInfoString(&buffer, "extension");
			break;

		case OCLASS_EVENT_TRIGGER:
			appendStringInfoString(&buffer, "event trigger");
			break;

		case OCLASS_POLICY:
			appendStringInfoString(&buffer, "policy");
			break;

		case OCLASS_PUBLICATION:
			appendStringInfoString(&buffer, "publication");
			break;

		case OCLASS_PUBLICATION_REL:
			appendStringInfoString(&buffer, "publication relation");
			break;

		case OCLASS_SUBSCRIPTION:
			appendStringInfoString(&buffer, "subscription");
			break;

		case OCLASS_TRANSFORM:
			appendStringInfoString(&buffer, "transform");
			break;

			/*
			 * There's intentionally no default: case here; we want the
			 * compiler to warn if a new OCLASS hasn't been handled above.
			 */
	}

	return buffer.data;
}