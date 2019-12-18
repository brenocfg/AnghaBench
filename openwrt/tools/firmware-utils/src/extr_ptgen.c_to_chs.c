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
 long heads ; 
 long sectors ; 

__attribute__((used)) static void to_chs(long sect, unsigned char chs[3])
{
	int c,h,s;

	s = (sect % sectors) + 1;
	sect = sect / sectors;
	h = sect % heads;
	sect = sect / heads;
	c = sect;

	chs[0] = h;
	chs[1] = s | ((c >> 2) & 0xC0);
	chs[2] = c & 0xFF;

	return;
}