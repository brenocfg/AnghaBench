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
struct vt8500lcd_info {scalar_t__ regbase; int /*<<< orphan*/  wait; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned int FBIO_WAITFORVSYNC ; 
 int HZ ; 
 int readl (scalar_t__) ; 
 struct vt8500lcd_info* to_vt8500lcd_info (struct fb_info*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int vt8500lcd_ioctl(struct fb_info *info, unsigned int cmd,
			 unsigned long arg)
{
	int ret = 0;
	struct vt8500lcd_info *fbi = to_vt8500lcd_info(info);

	if (cmd == FBIO_WAITFORVSYNC) {
		/* Unmask End of Frame interrupt */
		writel(0xffffffff ^ (1 << 3), fbi->regbase + 0x3c);
		ret = wait_event_interruptible_timeout(fbi->wait,
			readl(fbi->regbase + 0x38) & (1 << 3), HZ / 10);
		/* Mask back to reduce unwanted interrupt traffic */
		writel(0xffffffff, fbi->regbase + 0x3c);
		if (ret < 0)
			return ret;
		if (ret == 0)
			return -ETIMEDOUT;
	}

	return ret;
}