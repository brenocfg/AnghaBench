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

/* Variables and functions */

__attribute__((used)) static inline unsigned int userpolicy_type_attrsize(void)
{
#ifdef CONFIG_XFRM_SUB_POLICY
	return nla_total_size(sizeof(struct xfrm_userpolicy_type));
#else
	return 0;
#endif
}