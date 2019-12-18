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
typedef  int /*<<< orphan*/  Value ;
struct TYPE_3__ {int /*<<< orphan*/  objectSubId; void* objectId; void* classId; } ;
typedef  int ObjectType ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 void* AccessMethodRelationId ; 
 void* AuthIdRelationId ; 
 void* DatabaseRelationId ; 
 int /*<<< orphan*/  ERROR ; 
 void* EventTriggerRelationId ; 
 void* ExtensionRelationId ; 
 void* ForeignDataWrapperRelationId ; 
 void* ForeignServerRelationId ; 
 void* InvalidOid ; 
 void* LanguageRelationId ; 
 void* NamespaceRelationId ; 
#define  OBJECT_ACCESS_METHOD 139 
#define  OBJECT_DATABASE 138 
#define  OBJECT_EVENT_TRIGGER 137 
#define  OBJECT_EXTENSION 136 
#define  OBJECT_FDW 135 
#define  OBJECT_FOREIGN_SERVER 134 
#define  OBJECT_LANGUAGE 133 
#define  OBJECT_PUBLICATION 132 
#define  OBJECT_ROLE 131 
#define  OBJECT_SCHEMA 130 
#define  OBJECT_SUBSCRIPTION 129 
#define  OBJECT_TABLESPACE 128 
 void* PublicationRelationId ; 
 void* SubscriptionRelationId ; 
 void* TableSpaceRelationId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 void* get_am_oid (char const*,int) ; 
 void* get_database_oid (char const*,int) ; 
 void* get_event_trigger_oid (char const*,int) ; 
 void* get_extension_oid (char const*,int) ; 
 void* get_foreign_data_wrapper_oid (char const*,int) ; 
 void* get_foreign_server_oid (char const*,int) ; 
 void* get_language_oid (char const*,int) ; 
 void* get_namespace_oid (char const*,int) ; 
 void* get_publication_oid (char const*,int) ; 
 void* get_role_oid (char const*,int) ; 
 void* get_subscription_oid (char const*,int) ; 
 void* get_tablespace_oid (char const*,int) ; 
 char* strVal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ObjectAddress
get_object_address_unqualified(ObjectType objtype,
							   Value *strval, bool missing_ok)
{
	const char *name;
	ObjectAddress address;

	name = strVal(strval);

	/* Translate name to OID. */
	switch (objtype)
	{
		case OBJECT_ACCESS_METHOD:
			address.classId = AccessMethodRelationId;
			address.objectId = get_am_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_DATABASE:
			address.classId = DatabaseRelationId;
			address.objectId = get_database_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_EXTENSION:
			address.classId = ExtensionRelationId;
			address.objectId = get_extension_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_TABLESPACE:
			address.classId = TableSpaceRelationId;
			address.objectId = get_tablespace_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_ROLE:
			address.classId = AuthIdRelationId;
			address.objectId = get_role_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_SCHEMA:
			address.classId = NamespaceRelationId;
			address.objectId = get_namespace_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_LANGUAGE:
			address.classId = LanguageRelationId;
			address.objectId = get_language_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_FDW:
			address.classId = ForeignDataWrapperRelationId;
			address.objectId = get_foreign_data_wrapper_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_FOREIGN_SERVER:
			address.classId = ForeignServerRelationId;
			address.objectId = get_foreign_server_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_EVENT_TRIGGER:
			address.classId = EventTriggerRelationId;
			address.objectId = get_event_trigger_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_PUBLICATION:
			address.classId = PublicationRelationId;
			address.objectId = get_publication_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		case OBJECT_SUBSCRIPTION:
			address.classId = SubscriptionRelationId;
			address.objectId = get_subscription_oid(name, missing_ok);
			address.objectSubId = 0;
			break;
		default:
			elog(ERROR, "unrecognized objtype: %d", (int) objtype);
			/* placate compiler, which doesn't know elog won't return */
			address.classId = InvalidOid;
			address.objectId = InvalidOid;
			address.objectSubId = 0;
	}

	return address;
}