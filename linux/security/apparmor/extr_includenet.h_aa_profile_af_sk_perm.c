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
struct sock {int /*<<< orphan*/  sk_type; int /*<<< orphan*/  sk_family; } ;
struct common_audit_data {int dummy; } ;
struct aa_profile {int dummy; } ;

/* Variables and functions */
 int aa_profile_af_perm (struct aa_profile*,struct common_audit_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int aa_profile_af_sk_perm(struct aa_profile *profile,
					struct common_audit_data *sa,
					u32 request,
					struct sock *sk)
{
	return aa_profile_af_perm(profile, sa, request, sk->sk_family,
				  sk->sk_type);
}