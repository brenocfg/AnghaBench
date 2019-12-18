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
struct svc_cred {scalar_t__ cr_principal; int /*<<< orphan*/  cr_group_info; int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  groups_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gss_cred (struct svc_cred*) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
same_creds(struct svc_cred *cr1, struct svc_cred *cr2)
{
	if ((is_gss_cred(cr1) != is_gss_cred(cr2))
		|| (!uid_eq(cr1->cr_uid, cr2->cr_uid))
		|| (!gid_eq(cr1->cr_gid, cr2->cr_gid))
		|| !groups_equal(cr1->cr_group_info, cr2->cr_group_info))
		return false;
	/* XXX: check that cr_targ_princ fields match ? */
	if (cr1->cr_principal == cr2->cr_principal)
		return true;
	if (!cr1->cr_principal || !cr2->cr_principal)
		return false;
	return 0 == strcmp(cr1->cr_principal, cr2->cr_principal);
}