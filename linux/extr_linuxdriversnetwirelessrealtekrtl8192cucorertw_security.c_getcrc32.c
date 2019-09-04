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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ sint ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 scalar_t__ bcrc32initialized ; 
 int /*<<< orphan*/  crc32_init () ; 
 int* crc32_table ; 

__attribute__((used)) static u32 getcrc32(u8 *buf, sint len)
{
	u8 *p;
	u32  crc;
_func_enter_;	
	if (bcrc32initialized == 0) crc32_init();

	crc = 0xffffffff;       /* preload shift register, per CRC-32 spec */

	for (p = buf; len > 0; ++p, --len) 
	{
		crc = crc32_table[ (crc ^ *p) & 0xff] ^ (crc >> 8);
	}
_func_exit_;				
	return ~crc;    /* transmit complement, per CRC-32 spec */
}