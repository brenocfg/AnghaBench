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
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_ADDR_LEN ; 
 int /*<<< orphan*/  NVMEM_MAC_FILEID ; 
 int /*<<< orphan*/  nvmem_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

UINT8 nvmem_set_mac_address(UINT8 *mac)
{
	return  nvmem_write(NVMEM_MAC_FILEID, MAC_ADDR_LEN, 0, mac);
}