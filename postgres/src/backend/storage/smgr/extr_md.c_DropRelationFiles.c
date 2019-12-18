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
typedef  int /*<<< orphan*/  SMgrRelation ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  scalar_t__ ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBackendId ; 
 scalar_t__ MAX_FORKNUM ; 
 int /*<<< orphan*/  XLogDropRelation (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smgrclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrdounlinkall (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  smgropen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
DropRelationFiles(RelFileNode *delrels, int ndelrels, bool isRedo)
{
	SMgrRelation *srels;
	int			i;

	srels = palloc(sizeof(SMgrRelation) * ndelrels);
	for (i = 0; i < ndelrels; i++)
	{
		SMgrRelation srel = smgropen(delrels[i], InvalidBackendId);

		if (isRedo)
		{
			ForkNumber	fork;

			for (fork = 0; fork <= MAX_FORKNUM; fork++)
				XLogDropRelation(delrels[i], fork);
		}
		srels[i] = srel;
	}

	smgrdounlinkall(srels, ndelrels, isRedo);

	for (i = 0; i < ndelrels; i++)
		smgrclose(srels[i]);
	pfree(srels);
}