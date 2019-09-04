#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* hname; } ;
struct aa_profile {TYPE_2__ base; } ;
struct aa_ext {scalar_t__ start; scalar_t__ pos; } ;
struct TYPE_4__ {char const* ns; scalar_t__ pos; } ;
struct TYPE_6__ {char const* name; char const* info; int error; TYPE_1__ iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_APPARMOR_STATUS ; 
 int /*<<< orphan*/  DEFINE_AUDIT_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_NONE ; 
 int aa_audit (int /*<<< orphan*/ ,struct aa_profile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_current_raw_label () ; 
 TYPE_3__* aad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_cb ; 
 struct aa_profile* labels_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa ; 

__attribute__((used)) static int audit_iface(struct aa_profile *new, const char *ns_name,
		       const char *name, const char *info, struct aa_ext *e,
		       int error)
{
	struct aa_profile *profile = labels_profile(aa_current_raw_label());
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, NULL);
	if (e)
		aad(&sa)->iface.pos = e->pos - e->start;
	aad(&sa)->iface.ns = ns_name;
	if (new)
		aad(&sa)->name = new->base.hname;
	else
		aad(&sa)->name = name;
	aad(&sa)->info = info;
	aad(&sa)->error = error;

	return aa_audit(AUDIT_APPARMOR_STATUS, profile, &sa, audit_cb);
}