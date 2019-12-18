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
struct TYPE_6__ {TYPE_1__* hctl; } ;
struct TYPE_5__ {int /*<<< orphan*/  nsegs; int /*<<< orphan*/  max_bucket; scalar_t__ keysize; int /*<<< orphan*/  collisions; int /*<<< orphan*/  accesses; } ;
typedef  TYPE_2__ HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  hash_accesses ; 
 int /*<<< orphan*/  hash_collisions ; 
 int /*<<< orphan*/  hash_expansions ; 
 int /*<<< orphan*/  hash_get_num_entries (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 

void
hash_stats(const char *where, HTAB *hashp)
{
#ifdef HASH_STATISTICS
	fprintf(stderr, "%s: this HTAB -- accesses %ld collisions %ld\n",
			where, hashp->hctl->accesses, hashp->hctl->collisions);

	fprintf(stderr, "hash_stats: entries %ld keysize %ld maxp %u segmentcount %ld\n",
			hash_get_num_entries(hashp), (long) hashp->hctl->keysize,
			hashp->hctl->max_bucket, hashp->hctl->nsegs);
	fprintf(stderr, "%s: total accesses %ld total collisions %ld\n",
			where, hash_accesses, hash_collisions);
	fprintf(stderr, "hash_stats: total expansions %ld\n",
			hash_expansions);
#endif
}