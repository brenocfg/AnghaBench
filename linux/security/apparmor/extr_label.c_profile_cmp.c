#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ hname; } ;
struct aa_profile {TYPE_1__ base; int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int ns_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int profile_cmp(struct aa_profile *a, struct aa_profile *b)
{
	int res;

	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!a->ns);
	AA_BUG(!b->ns);
	AA_BUG(!a->base.hname);
	AA_BUG(!b->base.hname);

	if (a == b || a->base.hname == b->base.hname)
		return 0;
	res = ns_cmp(a->ns, b->ns);
	if (res)
		return res;

	return strcmp(a->base.hname, b->base.hname);
}