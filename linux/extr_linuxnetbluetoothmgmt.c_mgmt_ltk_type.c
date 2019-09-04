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
typedef  int /*<<< orphan*/  u8 ;
struct smp_ltk {int type; int /*<<< orphan*/  authenticated; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_LTK_AUTHENTICATED ; 
 int /*<<< orphan*/  MGMT_LTK_P256_AUTH ; 
 int /*<<< orphan*/  MGMT_LTK_P256_DEBUG ; 
 int /*<<< orphan*/  MGMT_LTK_P256_UNAUTH ; 
 int /*<<< orphan*/  MGMT_LTK_UNAUTHENTICATED ; 
#define  SMP_LTK 131 
#define  SMP_LTK_P256 130 
#define  SMP_LTK_P256_DEBUG 129 
#define  SMP_LTK_SLAVE 128 

__attribute__((used)) static u8 mgmt_ltk_type(struct smp_ltk *ltk)
{
	switch (ltk->type) {
	case SMP_LTK:
	case SMP_LTK_SLAVE:
		if (ltk->authenticated)
			return MGMT_LTK_AUTHENTICATED;
		return MGMT_LTK_UNAUTHENTICATED;
	case SMP_LTK_P256:
		if (ltk->authenticated)
			return MGMT_LTK_P256_AUTH;
		return MGMT_LTK_P256_UNAUTH;
	case SMP_LTK_P256_DEBUG:
		return MGMT_LTK_P256_DEBUG;
	}

	return MGMT_LTK_UNAUTHENTICATED;
}