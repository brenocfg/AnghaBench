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
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_3__ {scalar_t__ s_checksum_type; } ;
typedef  TYPE_1__ journal_superblock_t ;

/* Variables and functions */
 scalar_t__ JBD2_CRC32C_CHKSUM ; 
 int /*<<< orphan*/  jbd2_journal_has_csum_v2or3_feature (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jbd2_verify_csum_type(journal_t *j, journal_superblock_t *sb)
{
	if (!jbd2_journal_has_csum_v2or3_feature(j))
		return 1;

	return sb->s_checksum_type == JBD2_CRC32C_CHKSUM;
}