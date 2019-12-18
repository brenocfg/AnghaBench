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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  DEFINE_AUDIT_SK (int /*<<< orphan*/ ,char const*,struct sock*) ; 
 int /*<<< orphan*/  aa_profile_af_sk_perm (struct aa_profile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sock*) ; 
 int fn_for_each_confined (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa ; 
 int /*<<< orphan*/  unconfined (struct aa_label*) ; 

__attribute__((used)) static int aa_label_sk_perm(struct aa_label *label, const char *op, u32 request,
			    struct sock *sk)
{
	int error = 0;

	AA_BUG(!label);
	AA_BUG(!sk);

	if (!unconfined(label)) {
		struct aa_profile *profile;
		DEFINE_AUDIT_SK(sa, op, sk);

		error = fn_for_each_confined(label, profile,
			    aa_profile_af_sk_perm(profile, &sa, request, sk));
	}

	return error;
}