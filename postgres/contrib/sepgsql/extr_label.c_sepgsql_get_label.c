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
typedef  int /*<<< orphan*/  security_context_t ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int /*<<< orphan*/  objectSubId; void* objectId; void* classId; } ;
typedef  void* Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 char* GetSecurityLabel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  SEPGSQL_LABEL_TAG ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  freecon (int /*<<< orphan*/ ) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 scalar_t__ security_check_context_raw (int /*<<< orphan*/ ) ; 
 scalar_t__ security_get_initial_context_raw (char*,int /*<<< orphan*/ *) ; 

char *
sepgsql_get_label(Oid classId, Oid objectId, int32 subId)
{
	ObjectAddress object;
	char	   *label;

	object.classId = classId;
	object.objectId = objectId;
	object.objectSubId = subId;

	label = GetSecurityLabel(&object, SEPGSQL_LABEL_TAG);
	if (!label || security_check_context_raw((security_context_t) label))
	{
		security_context_t unlabeled;

		if (security_get_initial_context_raw("unlabeled", &unlabeled) < 0)
			ereport(ERROR,
					(errcode(ERRCODE_INTERNAL_ERROR),
					 errmsg("SELinux: failed to get initial security label: %m")));
		PG_TRY();
		{
			label = pstrdup(unlabeled);
		}
		PG_FINALLY();
		{
			freecon(unlabeled);
		}
		PG_END_TRY();
	}
	return label;
}