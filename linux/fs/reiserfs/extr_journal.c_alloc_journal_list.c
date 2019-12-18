#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct reiserfs_journal_list {int /*<<< orphan*/  j_commit_mutex; int /*<<< orphan*/  j_bh_list; int /*<<< orphan*/  j_tail_bh_list; int /*<<< orphan*/  j_working_list; int /*<<< orphan*/  j_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  j_num_lists; } ;

/* Variables and functions */
 int GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* SB_JOURNAL (struct super_block*) ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  get_journal_list (struct reiserfs_journal_list*) ; 
 struct reiserfs_journal_list* kzalloc (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct reiserfs_journal_list *alloc_journal_list(struct super_block *s)
{
	struct reiserfs_journal_list *jl;
	jl = kzalloc(sizeof(struct reiserfs_journal_list),
		     GFP_NOFS | __GFP_NOFAIL);
	INIT_LIST_HEAD(&jl->j_list);
	INIT_LIST_HEAD(&jl->j_working_list);
	INIT_LIST_HEAD(&jl->j_tail_bh_list);
	INIT_LIST_HEAD(&jl->j_bh_list);
	mutex_init(&jl->j_commit_mutex);
	SB_JOURNAL(s)->j_num_lists++;
	get_journal_list(jl);
	return jl;
}