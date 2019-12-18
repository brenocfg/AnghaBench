#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ idsubst; scalar_t__ posinsubst; scalar_t__ tnvariant; } ;
typedef  TYPE_1__ LexemeInfo ;

/* Variables and functions */

__attribute__((used)) static int
cmpLexemeInfo(LexemeInfo *a, LexemeInfo *b)
{
	if (a == NULL || b == NULL)
		return 0;

	if (a->idsubst == b->idsubst)
	{
		if (a->posinsubst == b->posinsubst)
		{
			if (a->tnvariant == b->tnvariant)
				return 0;

			return (a->tnvariant > b->tnvariant) ? 1 : -1;
		}

		return (a->posinsubst > b->posinsubst) ? 1 : -1;
	}

	return (a->idsubst > b->idsubst) ? 1 : -1;
}