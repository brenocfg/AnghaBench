#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;
struct TYPE_3__ {unsigned int rlim; unsigned long max; } ;
struct TYPE_4__ {char const* info; int error; struct aa_label* peer; TYPE_1__ rlim; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_APPARMOR_AUTO ; 
 int /*<<< orphan*/  DEFINE_AUDIT_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_NONE ; 
 int /*<<< orphan*/  OP_SETRLIMIT ; 
 int aa_audit (int /*<<< orphan*/ ,struct aa_profile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* aad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_cb ; 
 int /*<<< orphan*/  sa ; 

__attribute__((used)) static int audit_resource(struct aa_profile *profile, unsigned int resource,
			  unsigned long value, struct aa_label *peer,
			  const char *info, int error)
{
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, OP_SETRLIMIT);

	aad(&sa)->rlim.rlim = resource;
	aad(&sa)->rlim.max = value;
	aad(&sa)->peer = peer;
	aad(&sa)->info = info;
	aad(&sa)->error = error;

	return aa_audit(AUDIT_APPARMOR_AUTO, profile, &sa, audit_cb);
}