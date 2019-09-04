#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct aa_profile {int dummy; } ;
struct aa_perms {int audit; int allow; int kill; int quiet; } ;
struct aa_label {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
struct TYPE_8__ {char const* target; int /*<<< orphan*/  ouid; } ;
struct TYPE_11__ {int request; char const* name; char const* info; int error; int denied; TYPE_1__ fs; struct aa_label* peer; } ;
struct TYPE_9__ {int /*<<< orphan*/ * tsk; } ;
struct TYPE_10__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 scalar_t__ AUDIT_ALL ; 
 int AUDIT_APPARMOR_AUDIT ; 
 int AUDIT_APPARMOR_AUTO ; 
 int AUDIT_APPARMOR_KILL ; 
 scalar_t__ AUDIT_MODE (struct aa_profile*) ; 
 scalar_t__ AUDIT_NOQUIET ; 
 int /*<<< orphan*/  DEFINE_AUDIT_DATA (TYPE_3__,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_TASK ; 
 int aa_audit (int,struct aa_profile*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* aad (TYPE_3__*) ; 
 int /*<<< orphan*/  file_audit_cb ; 
 scalar_t__ likely (int) ; 
 TYPE_3__ sa ; 
 scalar_t__ unlikely (int) ; 

int aa_audit_file(struct aa_profile *profile, struct aa_perms *perms,
		  const char *op, u32 request, const char *name,
		  const char *target, struct aa_label *tlabel,
		  kuid_t ouid, const char *info, int error)
{
	int type = AUDIT_APPARMOR_AUTO;
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_TASK, op);

	sa.u.tsk = NULL;
	aad(&sa)->request = request;
	aad(&sa)->name = name;
	aad(&sa)->fs.target = target;
	aad(&sa)->peer = tlabel;
	aad(&sa)->fs.ouid = ouid;
	aad(&sa)->info = info;
	aad(&sa)->error = error;
	sa.u.tsk = NULL;

	if (likely(!aad(&sa)->error)) {
		u32 mask = perms->audit;

		if (unlikely(AUDIT_MODE(profile) == AUDIT_ALL))
			mask = 0xffff;

		/* mask off perms that are not being force audited */
		aad(&sa)->request &= mask;

		if (likely(!aad(&sa)->request))
			return 0;
		type = AUDIT_APPARMOR_AUDIT;
	} else {
		/* only report permissions that were denied */
		aad(&sa)->request = aad(&sa)->request & ~perms->allow;
		AA_BUG(!aad(&sa)->request);

		if (aad(&sa)->request & perms->kill)
			type = AUDIT_APPARMOR_KILL;

		/* quiet known rejects, assumes quiet and kill do not overlap */
		if ((aad(&sa)->request & perms->quiet) &&
		    AUDIT_MODE(profile) != AUDIT_NOQUIET &&
		    AUDIT_MODE(profile) != AUDIT_ALL)
			aad(&sa)->request &= ~perms->quiet;

		if (!aad(&sa)->request)
			return aad(&sa)->error;
	}

	aad(&sa)->denied = aad(&sa)->request & ~perms->allow;
	return aa_audit(type, profile, &sa, file_audit_cb);
}