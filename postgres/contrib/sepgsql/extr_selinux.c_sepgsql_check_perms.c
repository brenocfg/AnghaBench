#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct av_decision {int allowed; int auditdeny; int auditallow; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int SELINUX_AVD_FLAGS_PERMISSIVE ; 
 scalar_t__ SEPGSQL_MODE_INTERNAL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  sepgsql_audit_log (int,char const*,char const*,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  sepgsql_compute_avd (char const*,char const*,int /*<<< orphan*/ ,struct av_decision*) ; 
 scalar_t__ sepgsql_get_debug_audit () ; 
 scalar_t__ sepgsql_getenforce () ; 
 scalar_t__ sepgsql_mode ; 

bool
sepgsql_check_perms(const char *scontext,
					const char *tcontext,
					uint16 tclass,
					uint32 required,
					const char *audit_name,
					bool abort_on_violation)
{
	struct av_decision avd;
	uint32		denied;
	uint32		audited;
	bool		result = true;

	sepgsql_compute_avd(scontext, tcontext, tclass, &avd);

	denied = required & ~avd.allowed;

	if (sepgsql_get_debug_audit())
		audited = (denied ? denied : required);
	else
		audited = (denied ? (denied & avd.auditdeny)
				   : (required & avd.auditallow));

	if (denied &&
		sepgsql_getenforce() > 0 &&
		(avd.flags & SELINUX_AVD_FLAGS_PERMISSIVE) == 0)
		result = false;

	/*
	 * It records a security audit for the request, if needed. But, when
	 * SE-PgSQL performs 'internal' mode, it needs to keep silent.
	 */
	if (audited && sepgsql_mode != SEPGSQL_MODE_INTERNAL)
	{
		sepgsql_audit_log(denied,
						  scontext,
						  tcontext,
						  tclass,
						  audited,
						  audit_name);
	}

	if (!result && abort_on_violation)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("SELinux: security policy violation")));
	return result;
}