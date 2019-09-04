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
struct nlattr {int dummy; } ;
struct meta_value {unsigned long val; int len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 

__attribute__((used)) static int meta_var_change(struct meta_value *dst, struct nlattr *nla)
{
	int len = nla_len(nla);

	dst->val = (unsigned long)kmemdup(nla_data(nla), len, GFP_KERNEL);
	if (dst->val == 0UL)
		return -ENOMEM;
	dst->len = len;
	return 0;
}