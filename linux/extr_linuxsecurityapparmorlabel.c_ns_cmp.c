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
struct TYPE_2__ {int /*<<< orphan*/  hname; } ;
struct aa_ns {int level; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ns_cmp(struct aa_ns *a, struct aa_ns *b)
{
	int res;

	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!a->base.hname);
	AA_BUG(!b->base.hname);

	if (a == b)
		return 0;

	res = a->level - b->level;
	if (res)
		return res;

	return strcmp(a->base.hname, b->base.hname);
}