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
struct TYPE_5__ {int j_format_version; TYPE_2__* j_superblock; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_6__ {int /*<<< orphan*/  s_feature_incompat; int /*<<< orphan*/  s_feature_ro_compat; int /*<<< orphan*/  s_feature_compat; } ;
typedef  TYPE_2__ journal_superblock_t ;

/* Variables and functions */
 unsigned long be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ journal_get_superblock (TYPE_1__*) ; 

int jbd2_journal_check_used_features (journal_t *journal, unsigned long compat,
				 unsigned long ro, unsigned long incompat)
{
	journal_superblock_t *sb;

	if (!compat && !ro && !incompat)
		return 1;
	/* Load journal superblock if it is not loaded yet. */
	if (journal->j_format_version == 0 &&
	    journal_get_superblock(journal) != 0)
		return 0;
	if (journal->j_format_version == 1)
		return 0;

	sb = journal->j_superblock;

	if (((be32_to_cpu(sb->s_feature_compat) & compat) == compat) &&
	    ((be32_to_cpu(sb->s_feature_ro_compat) & ro) == ro) &&
	    ((be32_to_cpu(sb->s_feature_incompat) & incompat) == incompat))
		return 1;

	return 0;
}