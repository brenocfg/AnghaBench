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

/* Variables and functions */
 int POSITION_FOUND ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 

__attribute__((used)) static inline int indirect_item_found(int retval, struct item_head *ih)
{
	return (retval == POSITION_FOUND) && is_indirect_le_ih(ih);
}