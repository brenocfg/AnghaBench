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
typedef  int u8 ;

/* Variables and functions */
 int EINVAL ; 
#define  XFRM_POLICY_TYPE_MAIN 128 

__attribute__((used)) static int verify_policy_type(u8 type)
{
	switch (type) {
	case XFRM_POLICY_TYPE_MAIN:
#ifdef CONFIG_XFRM_SUB_POLICY
	case XFRM_POLICY_TYPE_SUB:
#endif
		break;

	default:
		return -EINVAL;
	}

	return 0;
}