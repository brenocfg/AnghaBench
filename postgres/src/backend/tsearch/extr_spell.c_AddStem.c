#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nstem; int lenstem; char** stem; } ;
typedef  TYPE_1__ SplitVar ;

/* Variables and functions */
 scalar_t__ repalloc (char**,int) ; 

__attribute__((used)) static void
AddStem(SplitVar *v, char *word)
{
	if (v->nstem >= v->lenstem)
	{
		v->lenstem *= 2;
		v->stem = (char **) repalloc(v->stem, sizeof(char *) * v->lenstem);
	}

	v->stem[v->nstem] = word;
	v->nstem++;
}