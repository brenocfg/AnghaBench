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

/* Variables and functions */

unsigned char read_dsp(unsigned short base)
{
//	while((inb(base+0x0e)&0x80)==0);	//Wait until there is something to read
//	return	inb(base+0x0a);
	return 0;
}