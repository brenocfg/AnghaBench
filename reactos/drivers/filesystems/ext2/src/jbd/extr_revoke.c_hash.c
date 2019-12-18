#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct jbd_revoke_table_s {int hash_shift; int hash_size; } ;
struct TYPE_3__ {struct jbd_revoke_table_s* j_revoke; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */

__attribute__((used)) static inline int hash(journal_t *journal, unsigned long block)
{
    struct jbd_revoke_table_s *table = journal->j_revoke;
    int hash_shift = table->hash_shift;

    return ((block << (hash_shift - 6)) ^
            (block >> 13) ^
            (block << (hash_shift - 12))) & (table->hash_size - 1);
}