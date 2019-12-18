#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* buffer; } ;
struct TYPE_5__ {int nTapes; struct TYPE_5__* freeBlocks; TYPE_2__* tapes; int /*<<< orphan*/  pfile; } ;
typedef  TYPE_1__ LogicalTapeSet ;
typedef  TYPE_2__ LogicalTape ;

/* Variables and functions */
 int /*<<< orphan*/  BufFileClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
LogicalTapeSetClose(LogicalTapeSet *lts)
{
	LogicalTape *lt;
	int			i;

	BufFileClose(lts->pfile);
	for (i = 0; i < lts->nTapes; i++)
	{
		lt = &lts->tapes[i];
		if (lt->buffer)
			pfree(lt->buffer);
	}
	pfree(lts->freeBlocks);
	pfree(lts);
}