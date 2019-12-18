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
struct item_head {int dummy; } ;
typedef  scalar_t__ b_blocknr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int POSITION_FOUND ; 
 scalar_t__ get_block_num (int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 

__attribute__((used)) static inline int allocation_needed(int retval, b_blocknr_t allocated,
				    struct item_head *ih,
				    __le32 * item, int pos_in_item)
{
	if (allocated)
		return 0;
	if (retval == POSITION_FOUND && is_indirect_le_ih(ih) &&
	    get_block_num(item, pos_in_item))
		return 0;
	return 1;
}