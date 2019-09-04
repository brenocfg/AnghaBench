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
struct TYPE_3__ {int /*<<< orphan*/  s_checksum; } ;
typedef  TYPE_1__ journal_superblock_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_chksum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static __be32 jbd2_superblock_csum(journal_t *j, journal_superblock_t *sb)
{
	__u32 csum;
	__be32 old_csum;

	old_csum = sb->s_checksum;
	sb->s_checksum = 0;
	csum = jbd2_chksum(j, ~0, (char *)sb, sizeof(journal_superblock_t));
	sb->s_checksum = old_csum;

	return cpu_to_be32(csum);
}