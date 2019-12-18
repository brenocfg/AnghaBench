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
typedef  unsigned long long u32 ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_3__ {void* t_blocknr_high; void* t_blocknr; } ;
typedef  TYPE_1__ journal_block_tag_t ;

/* Variables and functions */
 void* cpu_to_be32 (unsigned long long) ; 
 scalar_t__ jbd2_has_feature_64bit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_tag_block(journal_t *j, journal_block_tag_t *tag,
				   unsigned long long block)
{
	tag->t_blocknr = cpu_to_be32(block & (u32)~0);
	if (jbd2_has_feature_64bit(j))
		tag->t_blocknr_high = cpu_to_be32((block >> 31) >> 1);
}