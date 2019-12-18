#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16 ;
struct TYPE_7__ {scalar_t__ idsubst; scalar_t__ posinsubst; int tnvariant; struct TYPE_7__* nextentry; struct TYPE_7__* nextvariant; } ;
typedef  TYPE_1__ LexemeInfo ;

/* Variables and functions */
 scalar_t__ matchIdSubst (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static LexemeInfo *
findVariant(LexemeInfo *in, LexemeInfo *stored, uint16 curpos, LexemeInfo **newin, int newn)
{
	for (;;)
	{
		int			i;
		LexemeInfo *ptr = newin[0];

		for (i = 0; i < newn; i++)
		{
			while (newin[i] && newin[i]->idsubst < ptr->idsubst)
				newin[i] = newin[i]->nextentry;

			if (newin[i] == NULL)
				return in;

			if (newin[i]->idsubst > ptr->idsubst)
			{
				ptr = newin[i];
				i = -1;
				continue;
			}

			while (newin[i]->idsubst == ptr->idsubst)
			{
				if (newin[i]->posinsubst == curpos && newin[i]->tnvariant == newn)
				{
					ptr = newin[i];
					break;
				}

				newin[i] = newin[i]->nextentry;
				if (newin[i] == NULL)
					return in;
			}

			if (newin[i]->idsubst != ptr->idsubst)
			{
				ptr = newin[i];
				i = -1;
				continue;
			}
		}

		if (i == newn && matchIdSubst(stored, ptr->idsubst) && (in == NULL || !matchIdSubst(in, ptr->idsubst)))
		{						/* found */

			ptr->nextvariant = in;
			in = ptr;
		}

		/* step forward */
		for (i = 0; i < newn; i++)
			newin[i] = newin[i]->nextentry;
	}
}