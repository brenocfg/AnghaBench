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
struct tcf_defact {int /*<<< orphan*/  tcfd_defdata; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SIMP_MAX_DATA ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_strlcpy (int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int alloc_defdata(struct tcf_defact *d, const struct nlattr *defdata)
{
	d->tcfd_defdata = kzalloc(SIMP_MAX_DATA, GFP_KERNEL);
	if (unlikely(!d->tcfd_defdata))
		return -ENOMEM;
	nla_strlcpy(d->tcfd_defdata, defdata, SIMP_MAX_DATA);
	return 0;
}