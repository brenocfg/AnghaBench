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

void write_dsp(unsigned short base,unsigned char data)
{
//  while ((inb(base+DSP_WRITE_PORT) & 0x80) != 0);
//  outb(base+DSP_WRITE_PORT, data);
}