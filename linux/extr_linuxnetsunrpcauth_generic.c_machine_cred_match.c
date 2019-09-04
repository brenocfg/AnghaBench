#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ principal; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  machine_cred; } ;
struct generic_cred {TYPE_1__ acred; } ;
struct auth_cred {scalar_t__ principal; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
machine_cred_match(struct auth_cred *acred, struct generic_cred *gcred, int flags)
{
	if (!gcred->acred.machine_cred ||
	    gcred->acred.principal != acred->principal ||
	    !uid_eq(gcred->acred.uid, acred->uid) ||
	    !gid_eq(gcred->acred.gid, acred->gid))
		return 0;
	return 1;
}