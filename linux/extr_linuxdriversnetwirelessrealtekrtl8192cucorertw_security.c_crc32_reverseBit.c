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

/* Variables and functions */

__attribute__((used)) static u8 crc32_reverseBit( u8 data)
{
	return( (u8)((data<<7)&0x80) | ((data<<5)&0x40) | ((data<<3)&0x20) | ((data<<1)&0x10) | ((data>>1)&0x08) | ((data>>3)&0x04) | ((data>>5)&0x02) | ((data>>7)&0x01) );
}