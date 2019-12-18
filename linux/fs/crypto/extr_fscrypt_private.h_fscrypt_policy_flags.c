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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
union fscrypt_policy {int version; TYPE_2__ v2; TYPE_1__ v1; } ;
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  FSCRYPT_POLICY_V1 129 
#define  FSCRYPT_POLICY_V2 128 

__attribute__((used)) static inline u8
fscrypt_policy_flags(const union fscrypt_policy *policy)
{
	switch (policy->version) {
	case FSCRYPT_POLICY_V1:
		return policy->v1.flags;
	case FSCRYPT_POLICY_V2:
		return policy->v2.flags;
	}
	BUG();
}