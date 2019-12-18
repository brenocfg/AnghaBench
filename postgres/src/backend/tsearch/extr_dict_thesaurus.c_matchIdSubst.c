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
typedef  scalar_t__ uint32 ;
struct TYPE_3__ {scalar_t__ idsubst; struct TYPE_3__* nextvariant; } ;
typedef  TYPE_1__ LexemeInfo ;

/* Variables and functions */

__attribute__((used)) static bool
matchIdSubst(LexemeInfo *stored, uint32 idsubst)
{
	bool		res = true;

	if (stored)
	{
		res = false;

		for (; stored; stored = stored->nextvariant)
			if (stored->idsubst == idsubst)
			{
				res = true;
				break;
			}
	}

	return res;
}