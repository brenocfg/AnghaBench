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
struct TYPE_4__ {int nbatch; int /*<<< orphan*/  hashCxt; scalar_t__* outerBatchFile; scalar_t__* innerBatchFile; } ;
typedef  TYPE_1__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  BufFileClose (scalar_t__) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
ExecHashTableDestroy(HashJoinTable hashtable)
{
	int			i;

	/*
	 * Make sure all the temp files are closed.  We skip batch 0, since it
	 * can't have any temp files (and the arrays might not even exist if
	 * nbatch is only 1).  Parallel hash joins don't use these files.
	 */
	if (hashtable->innerBatchFile != NULL)
	{
		for (i = 1; i < hashtable->nbatch; i++)
		{
			if (hashtable->innerBatchFile[i])
				BufFileClose(hashtable->innerBatchFile[i]);
			if (hashtable->outerBatchFile[i])
				BufFileClose(hashtable->outerBatchFile[i]);
		}
	}

	/* Release working memory (batchCxt is a child, so it goes away too) */
	MemoryContextDelete(hashtable->hashCxt);

	/* And drop the control block */
	pfree(hashtable);
}