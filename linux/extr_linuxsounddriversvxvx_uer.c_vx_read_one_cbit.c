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
struct vx_core {scalar_t__ type; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUER ; 
 int /*<<< orphan*/  RUER ; 
 scalar_t__ VX_TYPE_VXPOCKET ; 
 int XX_UER_CBITS_OFFSET_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vx_inb (struct vx_core*,int /*<<< orphan*/ ) ; 
 int vx_inl (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outb (struct vx_core*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vx_outl (struct vx_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vx_read_one_cbit(struct vx_core *chip, int index)
{
	int val;

	mutex_lock(&chip->lock);
	if (chip->type >= VX_TYPE_VXPOCKET) {
		vx_outb(chip, CSUER, 1); /* read */
		vx_outb(chip, RUER, index & XX_UER_CBITS_OFFSET_MASK);
		val = (vx_inb(chip, RUER) >> 7) & 0x01;
	} else {
		vx_outl(chip, CSUER, 1); /* read */
		vx_outl(chip, RUER, index & XX_UER_CBITS_OFFSET_MASK);
		val = (vx_inl(chip, RUER) >> 7) & 0x01;
	}
	mutex_unlock(&chip->lock);
	return val;
}