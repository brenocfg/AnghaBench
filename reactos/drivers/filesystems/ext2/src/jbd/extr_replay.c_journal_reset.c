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
struct TYPE_5__ {unsigned long j_first; unsigned long j_last; unsigned long j_head; unsigned long j_tail; unsigned long j_free; int j_max_transaction_buffers; int j_maxlen; scalar_t__ j_commit_sequence; scalar_t__ j_commit_request; scalar_t__ j_transaction_sequence; scalar_t__ j_tail_sequence; TYPE_2__* j_superblock; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_6__ {int /*<<< orphan*/  s_maxlen; int /*<<< orphan*/  s_first; } ;
typedef  TYPE_2__ journal_superblock_t ;

/* Variables and functions */
 unsigned long be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_update_superblock (TYPE_1__*,int) ; 

__attribute__((used)) static int journal_reset(journal_t *journal)
{
    journal_superblock_t *sb = journal->j_superblock;
    unsigned long first, last;

    first = be32_to_cpu(sb->s_first);
    last = be32_to_cpu(sb->s_maxlen);

    journal->j_first = first;
    journal->j_last = last;

    journal->j_head = first;
    journal->j_tail = first;
    journal->j_free = last - first;

    journal->j_tail_sequence = journal->j_transaction_sequence;
    journal->j_commit_sequence = journal->j_transaction_sequence - 1;
    journal->j_commit_request = journal->j_commit_sequence;

    journal->j_max_transaction_buffers = journal->j_maxlen / 4;

    /* Add the dynamic fields and write it to disk. */
    journal_update_superblock(journal, 1);
    return 0;
}