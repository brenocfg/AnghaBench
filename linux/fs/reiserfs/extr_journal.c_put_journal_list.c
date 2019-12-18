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
struct super_block {int dummy; } ;
struct reiserfs_journal_list {int j_refcount; int /*<<< orphan*/  j_trans_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct reiserfs_journal_list*) ; 
 int /*<<< orphan*/  reiserfs_panic (struct super_block*,char*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void put_journal_list(struct super_block *s,
				    struct reiserfs_journal_list *jl)
{
	if (jl->j_refcount < 1) {
		reiserfs_panic(s, "journal-2", "trans id %u, refcount at %d",
			       jl->j_trans_id, jl->j_refcount);
	}
	if (--jl->j_refcount == 0)
		kfree(jl);
}