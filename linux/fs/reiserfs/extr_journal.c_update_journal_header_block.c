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
struct super_block {int dummy; } ;

/* Variables and functions */
 int _update_journal_header_block (struct super_block*,unsigned long,unsigned int) ; 

__attribute__((used)) static int update_journal_header_block(struct super_block *sb,
				       unsigned long offset,
				       unsigned int trans_id)
{
	return _update_journal_header_block(sb, offset, trans_id);
}