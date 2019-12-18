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
struct TYPE_3__ {scalar_t__ forkno; scalar_t__ blkno; int /*<<< orphan*/  node; } ;
struct TYPE_4__ {TYPE_1__ key; } ;
typedef  TYPE_2__ xl_invalid_page ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  scalar_t__ ForkNumber ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ DEBUG2 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 scalar_t__ RelFileNodeEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ client_min_messages ; 
 int /*<<< orphan*/  elog (scalar_t__,char*,...) ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * invalid_page_tab ; 
 scalar_t__ log_min_messages ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* relpathperm (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
forget_invalid_pages(RelFileNode node, ForkNumber forkno, BlockNumber minblkno)
{
	HASH_SEQ_STATUS status;
	xl_invalid_page *hentry;

	if (invalid_page_tab == NULL)
		return;					/* nothing to do */

	hash_seq_init(&status, invalid_page_tab);

	while ((hentry = (xl_invalid_page *) hash_seq_search(&status)) != NULL)
	{
		if (RelFileNodeEquals(hentry->key.node, node) &&
			hentry->key.forkno == forkno &&
			hentry->key.blkno >= minblkno)
		{
			if (log_min_messages <= DEBUG2 || client_min_messages <= DEBUG2)
			{
				char	   *path = relpathperm(hentry->key.node, forkno);

				elog(DEBUG2, "page %u of relation %s has been dropped",
					 hentry->key.blkno, path);
				pfree(path);
			}

			if (hash_search(invalid_page_tab,
							(void *) &hentry->key,
							HASH_REMOVE, NULL) == NULL)
				elog(ERROR, "hash table corrupted");
		}
	}
}