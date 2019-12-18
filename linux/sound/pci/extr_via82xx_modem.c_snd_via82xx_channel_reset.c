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
struct viadev {scalar_t__ lastpos; } ;
struct via82xx_modem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET_CONTROL ; 
 int /*<<< orphan*/  OFFSET_STATUS ; 
 int /*<<< orphan*/  OFFSET_TYPE ; 
 int /*<<< orphan*/  VIADEV_REG (struct viadev*,int /*<<< orphan*/ ) ; 
 int VIA_REG_CTRL_PAUSE ; 
 int VIA_REG_CTRL_RESET ; 
 int VIA_REG_CTRL_TERMINATE ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_via82xx_channel_reset(struct via82xx_modem *chip, struct viadev *viadev)
{
	outb(VIA_REG_CTRL_PAUSE | VIA_REG_CTRL_TERMINATE | VIA_REG_CTRL_RESET,
	     VIADEV_REG(viadev, OFFSET_CONTROL));
	inb(VIADEV_REG(viadev, OFFSET_CONTROL));
	udelay(50);
	/* disable interrupts */
	outb(0x00, VIADEV_REG(viadev, OFFSET_CONTROL));
	/* clear interrupts */
	outb(0x03, VIADEV_REG(viadev, OFFSET_STATUS));
	outb(0x00, VIADEV_REG(viadev, OFFSET_TYPE)); /* for via686 */
	// outl(0, VIADEV_REG(viadev, OFFSET_CURR_PTR));
	viadev->lastpos = 0;
}