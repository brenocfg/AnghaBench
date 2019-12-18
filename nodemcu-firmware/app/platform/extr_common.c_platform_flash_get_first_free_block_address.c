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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,scalar_t__) ; 
 scalar_t__ _flash_used_end ; 
 scalar_t__ flash_find_sector (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  platform_flash_mapped2phys (scalar_t__) ; 

uint32_t platform_flash_get_first_free_block_address( uint32_t *psect )
{
  // Round the total used flash size to the closest flash block address
  uint32_t start, end, sect;
  NODE_DBG("_flash_used_end:%08x\n", (uint32_t)_flash_used_end);
  if(_flash_used_end>0){ // find the used sector
    sect = flash_find_sector( platform_flash_mapped2phys ( (uint32_t)_flash_used_end - 1), NULL, &end );
    if( psect )
      *psect = sect + 1;
    return end + 1;
  } else {
    sect = flash_find_sector( 0, &start, NULL ); // find the first free sector
    if( psect )
      *psect = sect;
    return start;
  }
}