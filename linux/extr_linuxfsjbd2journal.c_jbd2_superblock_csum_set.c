#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_checksum; } ;
typedef  TYPE_1__ journal_superblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  jbd2_journal_has_csum_v2or3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_superblock_csum (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void jbd2_superblock_csum_set(journal_t *j, journal_superblock_t *sb)
{
	if (!jbd2_journal_has_csum_v2or3(j))
		return;

	sb->s_checksum = jbd2_superblock_csum(j, sb);
}