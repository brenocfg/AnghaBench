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
#define  XFRM_POLICY_FWD 130 
#define  XFRM_POLICY_IN 129 
#define  XFRM_POLICY_OUT 128 

__attribute__((used)) static int verify_policy_dir(u8 dir)
{
	switch (dir) {
	case XFRM_POLICY_IN:
	case XFRM_POLICY_OUT:
	case XFRM_POLICY_FWD:
		break;

	default:
		return -EINVAL;
	}

	return 0;
}