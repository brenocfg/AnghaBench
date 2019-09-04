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
typedef  scalar_t__ block_t ;

/* Variables and functions */
 scalar_t__ NEW_ADDR ; 
 scalar_t__ NULL_ADDR ; 

__attribute__((used)) static inline bool __is_valid_data_blkaddr(block_t blkaddr)
{
	if (blkaddr == NEW_ADDR || blkaddr == NULL_ADDR)
		return false;
	return true;
}