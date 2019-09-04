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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

__attribute__((used)) static void secmicputuint32( u8 * p, u32 val )
// Convert from Us4Byte32 to Byte[] in a portable way
{
	long i;
_func_enter_;			
	for( i=0; i<4; i++ )
	{
		*p++ = (u8) (val & 0xff);
		val >>= 8;
	}
_func_exit_;		
}