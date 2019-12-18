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
struct list_head {scalar_t__ next; } ;
struct jbd_revoke_record_s {unsigned long blocknr; struct list_head hash; } ;
struct TYPE_6__ {int /*<<< orphan*/  j_revoke_lock; TYPE_1__* j_revoke; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_5__ {struct list_head* hash_table; } ;

/* Variables and functions */
 size_t hash (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  jbd_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct jbd_revoke_record_s *find_revoke_record(journal_t *journal,
                    unsigned long blocknr)
{
    struct list_head *hash_list;
    struct jbd_revoke_record_s *record;

    hash_list = &journal->j_revoke->hash_table[hash(journal, blocknr)];

    jbd_lock(&journal->j_revoke_lock);
    record = (struct jbd_revoke_record_s *) hash_list->next;
    while (&(record->hash) != hash_list) {
        if (record->blocknr == blocknr) {
            jbd_unlock(&journal->j_revoke_lock);
            return record;
        }
        record = (struct jbd_revoke_record_s *) record->hash.next;
    }
    jbd_unlock(&journal->j_revoke_lock);
    return NULL;
}