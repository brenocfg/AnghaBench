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
struct TYPE_6__ {int keysize; int entrysize; scalar_t__ collisions; scalar_t__ accesses; int /*<<< orphan*/  sshift; int /*<<< orphan*/  ssize; int /*<<< orphan*/  max_dsize; int /*<<< orphan*/  ffactor; scalar_t__ num_partitions; scalar_t__ nsegs; int /*<<< orphan*/  dsize; } ;
struct TYPE_5__ {TYPE_2__* hctl; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ HASHHDR ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_DIRSIZE ; 
 int /*<<< orphan*/  DEF_FFACTOR ; 
 int /*<<< orphan*/  DEF_SEGSIZE ; 
 int /*<<< orphan*/  DEF_SEGSIZE_SHIFT ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NO_MAX_DSIZE ; 

__attribute__((used)) static void
hdefault(HTAB *hashp)
{
	HASHHDR    *hctl = hashp->hctl;

	MemSet(hctl, 0, sizeof(HASHHDR));

	hctl->dsize = DEF_DIRSIZE;
	hctl->nsegs = 0;

	/* rather pointless defaults for key & entry size */
	hctl->keysize = sizeof(char *);
	hctl->entrysize = 2 * sizeof(char *);

	hctl->num_partitions = 0;	/* not partitioned */

	hctl->ffactor = DEF_FFACTOR;

	/* table has no fixed maximum size */
	hctl->max_dsize = NO_MAX_DSIZE;

	hctl->ssize = DEF_SEGSIZE;
	hctl->sshift = DEF_SEGSIZE_SHIFT;

#ifdef HASH_STATISTICS
	hctl->accesses = hctl->collisions = 0;
#endif
}