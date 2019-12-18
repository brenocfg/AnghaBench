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
struct vx_core {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUER ; 
 int /*<<< orphan*/  RUER ; 
 int XX_UER_CBITS_OFFSET_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vx_is_pcmcia (struct vx_core*) ; 
 int /*<<< orphan*/  vx_outb (struct vx_core*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vx_outl (struct vx_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vx_write_one_cbit(struct vx_core *chip, int index, int val)
{
	val = !!val;	/* 0 or 1 */
	mutex_lock(&chip->lock);
	if (vx_is_pcmcia(chip)) {
		vx_outb(chip, CSUER, 0); /* write */
		vx_outb(chip, RUER, (val << 7) | (index & XX_UER_CBITS_OFFSET_MASK));
	} else {
		vx_outl(chip, CSUER, 0); /* write */
		vx_outl(chip, RUER, (val << 7) | (index & XX_UER_CBITS_OFFSET_MASK));
	}
	mutex_unlock(&chip->lock);
}