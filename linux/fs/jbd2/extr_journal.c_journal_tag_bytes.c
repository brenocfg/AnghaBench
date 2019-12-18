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
typedef  int /*<<< orphan*/  journal_t ;
typedef  int /*<<< orphan*/  journal_block_tag_t ;
typedef  int /*<<< orphan*/  journal_block_tag3_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ jbd2_has_feature_64bit (int /*<<< orphan*/ *) ; 
 scalar_t__ jbd2_has_feature_csum2 (int /*<<< orphan*/ *) ; 
 scalar_t__ jbd2_has_feature_csum3 (int /*<<< orphan*/ *) ; 

size_t journal_tag_bytes(journal_t *journal)
{
	size_t sz;

	if (jbd2_has_feature_csum3(journal))
		return sizeof(journal_block_tag3_t);

	sz = sizeof(journal_block_tag_t);

	if (jbd2_has_feature_csum2(journal))
		sz += sizeof(__u16);

	if (jbd2_has_feature_64bit(journal))
		return sz;
	else
		return sz - sizeof(__u32);
}