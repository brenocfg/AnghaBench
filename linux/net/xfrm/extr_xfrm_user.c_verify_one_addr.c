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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct nlattr {int dummy; } ;
typedef  enum xfrm_attr_type_t { ____Placeholder_xfrm_attr_type_t } xfrm_attr_type_t ;

/* Variables and functions */
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 

__attribute__((used)) static void verify_one_addr(struct nlattr **attrs, enum xfrm_attr_type_t type,
			   xfrm_address_t **addrp)
{
	struct nlattr *rt = attrs[type];

	if (rt && addrp)
		*addrp = nla_data(rt);
}