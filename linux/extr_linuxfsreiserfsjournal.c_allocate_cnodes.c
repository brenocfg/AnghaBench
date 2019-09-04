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
struct reiserfs_journal_cnode {struct reiserfs_journal_cnode* next; struct reiserfs_journal_cnode* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  array_size (int,int) ; 
 struct reiserfs_journal_cnode* vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct reiserfs_journal_cnode *allocate_cnodes(int num_cnodes)
{
	struct reiserfs_journal_cnode *head;
	int i;
	if (num_cnodes <= 0) {
		return NULL;
	}
	head = vzalloc(array_size(num_cnodes,
				  sizeof(struct reiserfs_journal_cnode)));
	if (!head) {
		return NULL;
	}
	head[0].prev = NULL;
	head[0].next = head + 1;
	for (i = 1; i < num_cnodes; i++) {
		head[i].prev = head + (i - 1);
		head[i].next = head + (i + 1);	/* if last one, overwrite it after the if */
	}
	head[num_cnodes - 1].next = NULL;
	return head;
}