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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

__attribute__((used)) static u32 secmicgetuint32( u8 * p )
// Convert from Byte[] to Us4Byte32 in a portable way
{
	s32 i;
	u32 res = 0;
_func_enter_;		
	for( i=0; i<4; i++ )
	{
		res |= ((u32)(*p++)) << (8*i);
	}
_func_exit_;		
	return res;
}