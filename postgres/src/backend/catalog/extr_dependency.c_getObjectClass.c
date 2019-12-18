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
struct TYPE_3__ {int classId; scalar_t__ objectSubId; } ;
typedef  int /*<<< orphan*/  ObjectClass ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
#define  AccessMethodOperatorRelationId 165 
#define  AccessMethodProcedureRelationId 164 
#define  AccessMethodRelationId 163 
#define  AttrDefaultRelationId 162 
#define  AuthIdRelationId 161 
#define  CastRelationId 160 
#define  CollationRelationId 159 
#define  ConstraintRelationId 158 
#define  ConversionRelationId 157 
#define  DatabaseRelationId 156 
#define  DefaultAclRelationId 155 
 int /*<<< orphan*/  ERROR ; 
#define  EventTriggerRelationId 154 
#define  ExtensionRelationId 153 
#define  ForeignDataWrapperRelationId 152 
#define  ForeignServerRelationId 151 
#define  LanguageRelationId 150 
#define  LargeObjectRelationId 149 
#define  NamespaceRelationId 148 
 int /*<<< orphan*/  OCLASS_AM ; 
 int /*<<< orphan*/  OCLASS_AMOP ; 
 int /*<<< orphan*/  OCLASS_AMPROC ; 
 int /*<<< orphan*/  OCLASS_CAST ; 
 int /*<<< orphan*/  OCLASS_CLASS ; 
 int /*<<< orphan*/  OCLASS_COLLATION ; 
 int /*<<< orphan*/  OCLASS_CONSTRAINT ; 
 int /*<<< orphan*/  OCLASS_CONVERSION ; 
 int /*<<< orphan*/  OCLASS_DATABASE ; 
 int /*<<< orphan*/  OCLASS_DEFACL ; 
 int /*<<< orphan*/  OCLASS_DEFAULT ; 
 int /*<<< orphan*/  OCLASS_EVENT_TRIGGER ; 
 int /*<<< orphan*/  OCLASS_EXTENSION ; 
 int /*<<< orphan*/  OCLASS_FDW ; 
 int /*<<< orphan*/  OCLASS_FOREIGN_SERVER ; 
 int /*<<< orphan*/  OCLASS_LANGUAGE ; 
 int /*<<< orphan*/  OCLASS_LARGEOBJECT ; 
 int /*<<< orphan*/  OCLASS_OPCLASS ; 
 int /*<<< orphan*/  OCLASS_OPERATOR ; 
 int /*<<< orphan*/  OCLASS_OPFAMILY ; 
 int /*<<< orphan*/  OCLASS_POLICY ; 
 int /*<<< orphan*/  OCLASS_PROC ; 
 int /*<<< orphan*/  OCLASS_PUBLICATION ; 
 int /*<<< orphan*/  OCLASS_PUBLICATION_REL ; 
 int /*<<< orphan*/  OCLASS_REWRITE ; 
 int /*<<< orphan*/  OCLASS_ROLE ; 
 int /*<<< orphan*/  OCLASS_SCHEMA ; 
 int /*<<< orphan*/  OCLASS_STATISTIC_EXT ; 
 int /*<<< orphan*/  OCLASS_SUBSCRIPTION ; 
 int /*<<< orphan*/  OCLASS_TBLSPACE ; 
 int /*<<< orphan*/  OCLASS_TRANSFORM ; 
 int /*<<< orphan*/  OCLASS_TRIGGER ; 
 int /*<<< orphan*/  OCLASS_TSCONFIG ; 
 int /*<<< orphan*/  OCLASS_TSDICT ; 
 int /*<<< orphan*/  OCLASS_TSPARSER ; 
 int /*<<< orphan*/  OCLASS_TSTEMPLATE ; 
 int /*<<< orphan*/  OCLASS_TYPE ; 
 int /*<<< orphan*/  OCLASS_USER_MAPPING ; 
#define  OperatorClassRelationId 147 
#define  OperatorFamilyRelationId 146 
#define  OperatorRelationId 145 
#define  PolicyRelationId 144 
#define  ProcedureRelationId 143 
#define  PublicationRelRelationId 142 
#define  PublicationRelationId 141 
#define  RelationRelationId 140 
#define  RewriteRelationId 139 
#define  StatisticExtRelationId 138 
#define  SubscriptionRelationId 137 
#define  TSConfigRelationId 136 
#define  TSDictionaryRelationId 135 
#define  TSParserRelationId 134 
#define  TSTemplateRelationId 133 
#define  TableSpaceRelationId 132 
#define  TransformRelationId 131 
#define  TriggerRelationId 130 
#define  TypeRelationId 129 
#define  UserMappingRelationId 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

ObjectClass
getObjectClass(const ObjectAddress *object)
{
	/* only pg_class entries can have nonzero objectSubId */
	if (object->classId != RelationRelationId &&
		object->objectSubId != 0)
		elog(ERROR, "invalid non-zero objectSubId for object class %u",
			 object->classId);

	switch (object->classId)
	{
		case RelationRelationId:
			/* caller must check objectSubId */
			return OCLASS_CLASS;

		case ProcedureRelationId:
			return OCLASS_PROC;

		case TypeRelationId:
			return OCLASS_TYPE;

		case CastRelationId:
			return OCLASS_CAST;

		case CollationRelationId:
			return OCLASS_COLLATION;

		case ConstraintRelationId:
			return OCLASS_CONSTRAINT;

		case ConversionRelationId:
			return OCLASS_CONVERSION;

		case AttrDefaultRelationId:
			return OCLASS_DEFAULT;

		case LanguageRelationId:
			return OCLASS_LANGUAGE;

		case LargeObjectRelationId:
			return OCLASS_LARGEOBJECT;

		case OperatorRelationId:
			return OCLASS_OPERATOR;

		case OperatorClassRelationId:
			return OCLASS_OPCLASS;

		case OperatorFamilyRelationId:
			return OCLASS_OPFAMILY;

		case AccessMethodRelationId:
			return OCLASS_AM;

		case AccessMethodOperatorRelationId:
			return OCLASS_AMOP;

		case AccessMethodProcedureRelationId:
			return OCLASS_AMPROC;

		case RewriteRelationId:
			return OCLASS_REWRITE;

		case TriggerRelationId:
			return OCLASS_TRIGGER;

		case NamespaceRelationId:
			return OCLASS_SCHEMA;

		case StatisticExtRelationId:
			return OCLASS_STATISTIC_EXT;

		case TSParserRelationId:
			return OCLASS_TSPARSER;

		case TSDictionaryRelationId:
			return OCLASS_TSDICT;

		case TSTemplateRelationId:
			return OCLASS_TSTEMPLATE;

		case TSConfigRelationId:
			return OCLASS_TSCONFIG;

		case AuthIdRelationId:
			return OCLASS_ROLE;

		case DatabaseRelationId:
			return OCLASS_DATABASE;

		case TableSpaceRelationId:
			return OCLASS_TBLSPACE;

		case ForeignDataWrapperRelationId:
			return OCLASS_FDW;

		case ForeignServerRelationId:
			return OCLASS_FOREIGN_SERVER;

		case UserMappingRelationId:
			return OCLASS_USER_MAPPING;

		case DefaultAclRelationId:
			return OCLASS_DEFACL;

		case ExtensionRelationId:
			return OCLASS_EXTENSION;

		case EventTriggerRelationId:
			return OCLASS_EVENT_TRIGGER;

		case PolicyRelationId:
			return OCLASS_POLICY;

		case PublicationRelationId:
			return OCLASS_PUBLICATION;

		case PublicationRelRelationId:
			return OCLASS_PUBLICATION_REL;

		case SubscriptionRelationId:
			return OCLASS_SUBSCRIPTION;

		case TransformRelationId:
			return OCLASS_TRANSFORM;
	}

	/* shouldn't get here */
	elog(ERROR, "unrecognized object class: %u", object->classId);
	return OCLASS_CLASS;		/* keep compiler quiet */
}