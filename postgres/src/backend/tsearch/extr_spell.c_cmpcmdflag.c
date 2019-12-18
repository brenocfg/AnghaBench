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
struct TYPE_3__ {scalar_t__ i; int /*<<< orphan*/  s; } ;
struct TYPE_4__ {scalar_t__ flagMode; TYPE_1__ flag; } ;
typedef  TYPE_2__ CompoundAffixFlag ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FM_NUM ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmpcmdflag(const void *f1, const void *f2)
{
	CompoundAffixFlag *fv1 = (CompoundAffixFlag *) f1,
			   *fv2 = (CompoundAffixFlag *) f2;

	Assert(fv1->flagMode == fv2->flagMode);

	if (fv1->flagMode == FM_NUM)
	{
		if (fv1->flag.i == fv2->flag.i)
			return 0;

		return (fv1->flag.i > fv2->flag.i) ? 1 : -1;
	}

	return strcmp(fv1->flag.s, fv2->flag.s);
}