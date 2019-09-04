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
struct csio_hw {int dummy; } ;

/* Variables and functions */
 unsigned int FLASH_CFG_START ; 

__attribute__((used)) static unsigned int
csio_t5_flash_cfg_addr(struct csio_hw *hw)
{
	return FLASH_CFG_START;
}