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
typedef  int /*<<< orphan*/  tid_t ;
struct list_head {int dummy; } ;
struct jbd2_revoke_record_s {unsigned long long blocknr; int /*<<< orphan*/  hash; int /*<<< orphan*/  sequence; } ;
struct TYPE_6__ {int /*<<< orphan*/  j_revoke_lock; TYPE_1__* j_revoke; } ;
typedef  TYPE_2__ journal_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {struct list_head* hash_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  __GFP_NOFAIL ; 
 size_t hash (TYPE_2__*,unsigned long long) ; 
 int /*<<< orphan*/  jbd2_revoke_record_cache ; 
 scalar_t__ journal_oom_retry ; 
 struct jbd2_revoke_record_s* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int insert_revoke_hash(journal_t *journal, unsigned long long blocknr,
			      tid_t seq)
{
	struct list_head *hash_list;
	struct jbd2_revoke_record_s *record;
	gfp_t gfp_mask = GFP_NOFS;

	if (journal_oom_retry)
		gfp_mask |= __GFP_NOFAIL;
	record = kmem_cache_alloc(jbd2_revoke_record_cache, gfp_mask);
	if (!record)
		return -ENOMEM;

	record->sequence = seq;
	record->blocknr = blocknr;
	hash_list = &journal->j_revoke->hash_table[hash(journal, blocknr)];
	spin_lock(&journal->j_revoke_lock);
	list_add(&record->hash, hash_list);
	spin_unlock(&journal->j_revoke_lock);
	return 0;
}