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
typedef  int u_int ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int chipsfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			     u_int transp, struct fb_info *info)
{
	if (regno > 255)
		return 1;
	red >>= 8;
	green >>= 8;
	blue >>= 8;
	outb(regno, 0x3c8);
	udelay(1);
	outb(red, 0x3c9);
	outb(green, 0x3c9);
	outb(blue, 0x3c9);

	return 0;
}