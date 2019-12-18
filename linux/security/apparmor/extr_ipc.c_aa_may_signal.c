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
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;
struct TYPE_2__ {int unmappedsig; int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_AUDIT_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_NONE ; 
 int /*<<< orphan*/  MAY_READ ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  OP_SIGNAL ; 
 TYPE_1__* aad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_signal_num (int) ; 
 int /*<<< orphan*/  profile_signal_perm (struct aa_profile*,struct aa_label*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa ; 
 int xcheck_labels (struct aa_label*,struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int aa_may_signal(struct aa_label *sender, struct aa_label *target, int sig)
{
	struct aa_profile *profile;
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, OP_SIGNAL);

	aad(&sa)->signal = map_signal_num(sig);
	aad(&sa)->unmappedsig = sig;
	return xcheck_labels(sender, target, profile,
			profile_signal_perm(profile, target, MAY_WRITE, &sa),
			profile_signal_perm(profile, sender, MAY_READ, &sa));
}