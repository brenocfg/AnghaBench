#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  createdb_dtemplate; } ;
struct TYPE_9__ {int dropflags; } ;
struct TYPE_8__ {int result; int /*<<< orphan*/  ereport_on_violation; } ;
struct TYPE_7__ {int is_internal; } ;
struct TYPE_6__ {int is_internal; } ;
typedef  int const Oid ;
typedef  int ObjectAccessType ;
typedef  TYPE_1__ ObjectAccessPostCreate ;
typedef  TYPE_2__ ObjectAccessPostAlter ;
typedef  TYPE_3__ ObjectAccessNamespaceSearch ;
typedef  TYPE_4__ ObjectAccessDrop ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  DatabaseRelationId 136 
 int /*<<< orphan*/  ERROR ; 
#define  NamespaceRelationId 135 
#define  OAT_DROP 134 
#define  OAT_FUNCTION_EXECUTE 133 
#define  OAT_NAMESPACE_SEARCH 132 
#define  OAT_POST_ALTER 131 
#define  OAT_POST_CREATE 130 
 int PERFORM_DELETION_INTERNAL ; 
#define  ProcedureRelationId 129 
#define  RelationRelationId 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  next_object_access_hook (int,int const,int const,int,void*) ; 
 int /*<<< orphan*/  sepgsql_attribute_drop (int const,int) ; 
 int /*<<< orphan*/  sepgsql_attribute_post_create (int const,int) ; 
 int /*<<< orphan*/  sepgsql_attribute_setattr (int const,int) ; 
 TYPE_5__ sepgsql_context_info ; 
 int /*<<< orphan*/  sepgsql_database_drop (int const) ; 
 int /*<<< orphan*/  sepgsql_database_post_create (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sepgsql_database_setattr (int const) ; 
 int /*<<< orphan*/  sepgsql_proc_drop (int const) ; 
 int /*<<< orphan*/  sepgsql_proc_execute (int const) ; 
 int /*<<< orphan*/  sepgsql_proc_post_create (int const) ; 
 int /*<<< orphan*/  sepgsql_proc_setattr (int const) ; 
 int /*<<< orphan*/  sepgsql_relation_drop (int const) ; 
 int /*<<< orphan*/  sepgsql_relation_post_create (int const) ; 
 int /*<<< orphan*/  sepgsql_relation_setattr (int const) ; 
 int /*<<< orphan*/  sepgsql_schema_drop (int const) ; 
 int /*<<< orphan*/  sepgsql_schema_post_create (int const) ; 
 int sepgsql_schema_search (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sepgsql_schema_setattr (int const) ; 
 int /*<<< orphan*/  stub1 (int,int const,int const,int,void*) ; 

__attribute__((used)) static void
sepgsql_object_access(ObjectAccessType access,
					  Oid classId,
					  Oid objectId,
					  int subId,
					  void *arg)
{
	if (next_object_access_hook)
		(*next_object_access_hook) (access, classId, objectId, subId, arg);

	switch (access)
	{
		case OAT_POST_CREATE:
			{
				ObjectAccessPostCreate *pc_arg = arg;
				bool		is_internal;

				is_internal = pc_arg ? pc_arg->is_internal : false;

				switch (classId)
				{
					case DatabaseRelationId:
						Assert(!is_internal);
						sepgsql_database_post_create(objectId,
													 sepgsql_context_info.createdb_dtemplate);
						break;

					case NamespaceRelationId:
						Assert(!is_internal);
						sepgsql_schema_post_create(objectId);
						break;

					case RelationRelationId:
						if (subId == 0)
						{
							/*
							 * The cases in which we want to apply permission
							 * checks on creation of a new relation correspond
							 * to direct user invocation.  For internal uses,
							 * that is creation of toast tables, index rebuild
							 * or ALTER TABLE commands, we need neither
							 * assignment of security labels nor permission
							 * checks.
							 */
							if (is_internal)
								break;

							sepgsql_relation_post_create(objectId);
						}
						else
							sepgsql_attribute_post_create(objectId, subId);
						break;

					case ProcedureRelationId:
						Assert(!is_internal);
						sepgsql_proc_post_create(objectId);
						break;

					default:
						/* Ignore unsupported object classes */
						break;
				}
			}
			break;

		case OAT_DROP:
			{
				ObjectAccessDrop *drop_arg = (ObjectAccessDrop *) arg;

				/*
				 * No need to apply permission checks on object deletion due
				 * to internal cleanups; such as removal of temporary database
				 * object on session closed.
				 */
				if ((drop_arg->dropflags & PERFORM_DELETION_INTERNAL) != 0)
					break;

				switch (classId)
				{
					case DatabaseRelationId:
						sepgsql_database_drop(objectId);
						break;

					case NamespaceRelationId:
						sepgsql_schema_drop(objectId);
						break;

					case RelationRelationId:
						if (subId == 0)
							sepgsql_relation_drop(objectId);
						else
							sepgsql_attribute_drop(objectId, subId);
						break;

					case ProcedureRelationId:
						sepgsql_proc_drop(objectId);
						break;

					default:
						/* Ignore unsupported object classes */
						break;
				}
			}
			break;

		case OAT_POST_ALTER:
			{
				ObjectAccessPostAlter *pa_arg = arg;
				bool		is_internal = pa_arg->is_internal;

				switch (classId)
				{
					case DatabaseRelationId:
						Assert(!is_internal);
						sepgsql_database_setattr(objectId);
						break;

					case NamespaceRelationId:
						Assert(!is_internal);
						sepgsql_schema_setattr(objectId);
						break;

					case RelationRelationId:
						if (subId == 0)
						{
							/*
							 * A case when we don't want to apply permission
							 * check is that relation is internally altered
							 * without user's intention. E.g, no need to check
							 * on toast table/index to be renamed at end of
							 * the table rewrites.
							 */
							if (is_internal)
								break;

							sepgsql_relation_setattr(objectId);
						}
						else
							sepgsql_attribute_setattr(objectId, subId);
						break;

					case ProcedureRelationId:
						Assert(!is_internal);
						sepgsql_proc_setattr(objectId);
						break;

					default:
						/* Ignore unsupported object classes */
						break;
				}
			}
			break;

		case OAT_NAMESPACE_SEARCH:
			{
				ObjectAccessNamespaceSearch *ns_arg = arg;

				/*
				 * If stacked extension already decided not to allow users to
				 * search this schema, we just stick with that decision.
				 */
				if (!ns_arg->result)
					break;

				Assert(classId == NamespaceRelationId);
				Assert(ns_arg->result);
				ns_arg->result
					= sepgsql_schema_search(objectId,
											ns_arg->ereport_on_violation);
			}
			break;

		case OAT_FUNCTION_EXECUTE:
			{
				Assert(classId == ProcedureRelationId);
				sepgsql_proc_execute(objectId);
			}
			break;

		default:
			elog(ERROR, "unexpected object access type: %d", (int) access);
			break;
	}
}