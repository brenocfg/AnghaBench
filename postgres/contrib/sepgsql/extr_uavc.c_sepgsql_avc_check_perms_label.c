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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_3__ {int allowed; int auditdeny; int auditallow; char const* tcontext; int /*<<< orphan*/  tclass; scalar_t__ tcontext_is_valid; int /*<<< orphan*/  scontext; scalar_t__ permissive; } ;
typedef  TYPE_1__ avc_cache ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 char const* SEPGSQL_AVC_NOAUDIT ; 
 scalar_t__ SEPGSQL_MODE_INTERNAL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  sepgsql_audit_log (int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_valid () ; 
 TYPE_1__* sepgsql_avc_lookup (char*,char const*,int /*<<< orphan*/ ) ; 
 char const* sepgsql_avc_unlabeled () ; 
 char* sepgsql_get_client_label () ; 
 scalar_t__ sepgsql_get_debug_audit () ; 
 scalar_t__ sepgsql_get_mode () ; 
 int /*<<< orphan*/  sepgsql_getenforce () ; 

bool
sepgsql_avc_check_perms_label(const char *tcontext,
							  uint16 tclass, uint32 required,
							  const char *audit_name,
							  bool abort_on_violation)
{
	char	   *scontext = sepgsql_get_client_label();
	avc_cache  *cache;
	uint32		denied;
	uint32		audited;
	bool		result;

	sepgsql_avc_check_valid();
	do
	{
		result = true;

		/*
		 * If the target object is unlabeled, we perform the check using the
		 * label supplied by sepgsql_avc_unlabeled().
		 */
		if (tcontext)
			cache = sepgsql_avc_lookup(scontext, tcontext, tclass);
		else
			cache = sepgsql_avc_lookup(scontext,
									   sepgsql_avc_unlabeled(), tclass);

		denied = required & ~cache->allowed;

		/*
		 * Compute permissions to be audited
		 */
		if (sepgsql_get_debug_audit())
			audited = (denied ? (denied & ~0) : (required & ~0));
		else
			audited = denied ? (denied & cache->auditdeny)
				: (required & cache->auditallow);

		if (denied)
		{
			/*
			 * In permissive mode or permissive domain, violated permissions
			 * shall be audited to the log files at once, and then implicitly
			 * allowed to avoid a flood of access denied logs, because the
			 * purpose of permissive mode/domain is to collect a violation log
			 * that will make it possible to fix up the security policy.
			 */
			if (!sepgsql_getenforce() || cache->permissive)
				cache->allowed |= required;
			else
				result = false;
		}
	} while (!sepgsql_avc_check_valid());

	/*
	 * In the case when we have something auditable actions here,
	 * sepgsql_audit_log shall be called with text representation of security
	 * labels for both of subject and object. It records this access
	 * violation, so DBA will be able to find out unexpected security problems
	 * later.
	 */
	if (audited != 0 &&
		audit_name != SEPGSQL_AVC_NOAUDIT &&
		sepgsql_get_mode() != SEPGSQL_MODE_INTERNAL)
	{
		sepgsql_audit_log(denied != 0,
						  cache->scontext,
						  cache->tcontext_is_valid ?
						  cache->tcontext : sepgsql_avc_unlabeled(),
						  cache->tclass,
						  audited,
						  audit_name);
	}

	if (abort_on_violation && !result)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("SELinux: security policy violation")));

	return result;
}