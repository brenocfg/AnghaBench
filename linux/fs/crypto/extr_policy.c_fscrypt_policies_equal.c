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
union fscrypt_policy {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  fscrypt_policy_size (union fscrypt_policy const*) ; 
 int /*<<< orphan*/  memcmp (union fscrypt_policy const*,union fscrypt_policy const*,int /*<<< orphan*/ ) ; 

bool fscrypt_policies_equal(const union fscrypt_policy *policy1,
			    const union fscrypt_policy *policy2)
{
	if (policy1->version != policy2->version)
		return false;

	return !memcmp(policy1, policy2, fscrypt_policy_size(policy1));
}