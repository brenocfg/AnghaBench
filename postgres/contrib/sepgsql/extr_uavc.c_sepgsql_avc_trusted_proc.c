#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* ncontext; } ;
typedef  TYPE_1__ avc_cache ;
struct TYPE_6__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectAddress ;

/* Variables and functions */
 char* GetSecurityLabel (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  SEPGSQL_LABEL_TAG ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_PROCEDURE ; 
 int /*<<< orphan*/  sepgsql_avc_check_valid () ; 
 TYPE_1__* sepgsql_avc_lookup (char*,char*,int /*<<< orphan*/ ) ; 
 char* sepgsql_avc_unlabeled () ; 
 char* sepgsql_get_client_label () ; 

char *
sepgsql_avc_trusted_proc(Oid functionId)
{
	char	   *scontext = sepgsql_get_client_label();
	char	   *tcontext;
	ObjectAddress tobject;
	avc_cache  *cache;

	tobject.classId = ProcedureRelationId;
	tobject.objectId = functionId;
	tobject.objectSubId = 0;
	tcontext = GetSecurityLabel(&tobject, SEPGSQL_LABEL_TAG);

	sepgsql_avc_check_valid();
	do
	{
		if (tcontext)
			cache = sepgsql_avc_lookup(scontext, tcontext,
									   SEPG_CLASS_DB_PROCEDURE);
		else
			cache = sepgsql_avc_lookup(scontext, sepgsql_avc_unlabeled(),
									   SEPG_CLASS_DB_PROCEDURE);
	} while (!sepgsql_avc_check_valid());

	return cache->ncontext;
}