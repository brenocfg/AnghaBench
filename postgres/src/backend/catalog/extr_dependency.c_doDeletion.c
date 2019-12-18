#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  objectSubId; } ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DeleteSequenceTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DropCastById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DropProceduralLanguageById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DropTransformById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LargeObjectDrop (int /*<<< orphan*/ ) ; 
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
 int PERFORM_DELETION_CONCURRENTLY ; 
 int PERFORM_DELETION_CONCURRENT_LOCK ; 
 char RELKIND_INDEX ; 
 char RELKIND_PARTITIONED_INDEX ; 
 char RELKIND_SEQUENCE ; 
 int /*<<< orphan*/  RemoveAccessMethodById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveAmOpEntryById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveAmProcEntryById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveAttrDefaultById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveAttributeById (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveCollationById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveConstraintById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveConversionById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveDefaultACLById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveEventTriggerById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveExtensionById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveForeignDataWrapperById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveForeignServerById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveFunctionById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveOpClassById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveOpFamilyById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveOperatorById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemovePolicyById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemovePublicationById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemovePublicationRelById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveRewriteRuleById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveSchemaById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveStatisticsById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveTSConfigurationById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveTSDictionaryById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveTSParserById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveTSTemplateById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveTriggerById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveTypeById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveUserMappingById (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int getObjectClass (TYPE_1__ const*) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_drop_with_catalog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_drop (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
doDeletion(const ObjectAddress *object, int flags)
{
	switch (getObjectClass(object))
	{
		case OCLASS_CLASS:
			{
				char		relKind = get_rel_relkind(object->objectId);

				if (relKind == RELKIND_INDEX ||
					relKind == RELKIND_PARTITIONED_INDEX)
				{
					bool		concurrent = ((flags & PERFORM_DELETION_CONCURRENTLY) != 0);
					bool		concurrent_lock_mode = ((flags & PERFORM_DELETION_CONCURRENT_LOCK) != 0);

					Assert(object->objectSubId == 0);
					index_drop(object->objectId, concurrent, concurrent_lock_mode);
				}
				else
				{
					if (object->objectSubId != 0)
						RemoveAttributeById(object->objectId,
											object->objectSubId);
					else
						heap_drop_with_catalog(object->objectId);
				}

				/*
				 * for a sequence, in addition to dropping the heap, also
				 * delete pg_sequence tuple
				 */
				if (relKind == RELKIND_SEQUENCE)
					DeleteSequenceTuple(object->objectId);
				break;
			}

		case OCLASS_PROC:
			RemoveFunctionById(object->objectId);
			break;

		case OCLASS_TYPE:
			RemoveTypeById(object->objectId);
			break;

		case OCLASS_CAST:
			DropCastById(object->objectId);
			break;

		case OCLASS_COLLATION:
			RemoveCollationById(object->objectId);
			break;

		case OCLASS_CONSTRAINT:
			RemoveConstraintById(object->objectId);
			break;

		case OCLASS_CONVERSION:
			RemoveConversionById(object->objectId);
			break;

		case OCLASS_DEFAULT:
			RemoveAttrDefaultById(object->objectId);
			break;

		case OCLASS_LANGUAGE:
			DropProceduralLanguageById(object->objectId);
			break;

		case OCLASS_LARGEOBJECT:
			LargeObjectDrop(object->objectId);
			break;

		case OCLASS_OPERATOR:
			RemoveOperatorById(object->objectId);
			break;

		case OCLASS_OPCLASS:
			RemoveOpClassById(object->objectId);
			break;

		case OCLASS_OPFAMILY:
			RemoveOpFamilyById(object->objectId);
			break;

		case OCLASS_AM:
			RemoveAccessMethodById(object->objectId);
			break;

		case OCLASS_AMOP:
			RemoveAmOpEntryById(object->objectId);
			break;

		case OCLASS_AMPROC:
			RemoveAmProcEntryById(object->objectId);
			break;

		case OCLASS_REWRITE:
			RemoveRewriteRuleById(object->objectId);
			break;

		case OCLASS_TRIGGER:
			RemoveTriggerById(object->objectId);
			break;

		case OCLASS_SCHEMA:
			RemoveSchemaById(object->objectId);
			break;

		case OCLASS_STATISTIC_EXT:
			RemoveStatisticsById(object->objectId);
			break;

		case OCLASS_TSPARSER:
			RemoveTSParserById(object->objectId);
			break;

		case OCLASS_TSDICT:
			RemoveTSDictionaryById(object->objectId);
			break;

		case OCLASS_TSTEMPLATE:
			RemoveTSTemplateById(object->objectId);
			break;

		case OCLASS_TSCONFIG:
			RemoveTSConfigurationById(object->objectId);
			break;

			/*
			 * OCLASS_ROLE, OCLASS_DATABASE, OCLASS_TBLSPACE intentionally not
			 * handled here
			 */

		case OCLASS_FDW:
			RemoveForeignDataWrapperById(object->objectId);
			break;

		case OCLASS_FOREIGN_SERVER:
			RemoveForeignServerById(object->objectId);
			break;

		case OCLASS_USER_MAPPING:
			RemoveUserMappingById(object->objectId);
			break;

		case OCLASS_DEFACL:
			RemoveDefaultACLById(object->objectId);
			break;

		case OCLASS_EXTENSION:
			RemoveExtensionById(object->objectId);
			break;

		case OCLASS_EVENT_TRIGGER:
			RemoveEventTriggerById(object->objectId);
			break;

		case OCLASS_POLICY:
			RemovePolicyById(object->objectId);
			break;

		case OCLASS_PUBLICATION:
			RemovePublicationById(object->objectId);
			break;

		case OCLASS_PUBLICATION_REL:
			RemovePublicationRelById(object->objectId);
			break;

		case OCLASS_TRANSFORM:
			DropTransformById(object->objectId);
			break;

			/*
			 * These global object types are not supported here.
			 */
		case OCLASS_ROLE:
		case OCLASS_DATABASE:
		case OCLASS_TBLSPACE:
		case OCLASS_SUBSCRIPTION:
			elog(ERROR, "global objects cannot be deleted by doDeletion");
			break;

			/*
			 * There's intentionally no default: case here; we want the
			 * compiler to warn if a new OCLASS hasn't been handled above.
			 */
	}
}