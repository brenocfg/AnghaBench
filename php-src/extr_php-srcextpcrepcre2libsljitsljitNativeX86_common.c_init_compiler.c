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
typedef  int sljit_uw ;
typedef  int sljit_s32 ;

/* Variables and functions */
 int* sse2_buffer ; 
 scalar_t__ sse2_data ; 

__attribute__((used)) static void init_compiler(void)
{
	/* Align to 16 bytes. */
	sse2_buffer = (sljit_s32*)(((sljit_uw)sse2_data + 15) & ~0xf);

	/* Single precision constants (each constant is 16 byte long). */
	sse2_buffer[0] = 0x80000000;
	sse2_buffer[4] = 0x7fffffff;
	/* Double precision constants (each constant is 16 byte long). */
	sse2_buffer[8] = 0;
	sse2_buffer[9] = 0x80000000;
	sse2_buffer[12] = 0xffffffff;
	sse2_buffer[13] = 0x7fffffff;
}