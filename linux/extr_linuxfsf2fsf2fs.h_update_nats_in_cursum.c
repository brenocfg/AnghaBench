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
struct f2fs_journal {int /*<<< orphan*/  n_nats; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int nats_in_cursum (struct f2fs_journal*) ; 

__attribute__((used)) static inline int update_nats_in_cursum(struct f2fs_journal *journal, int i)
{
	int before = nats_in_cursum(journal);

	journal->n_nats = cpu_to_le16(before + i);
	return before;
}