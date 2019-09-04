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
typedef  unsigned int u32 ;
struct sh_pfc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GENMASK (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int sh_pfc_pinconf_find_drive_strength_reg (struct sh_pfc*,unsigned int,unsigned int*,unsigned int*) ; 
 unsigned int sh_pfc_read (struct sh_pfc*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh_pfc_pinconf_get_drive_strength(struct sh_pfc *pfc,
					     unsigned int pin)
{
	unsigned long flags;
	unsigned int offset;
	unsigned int size;
	u32 reg;
	u32 val;

	reg = sh_pfc_pinconf_find_drive_strength_reg(pfc, pin, &offset, &size);
	if (!reg)
		return -EINVAL;

	spin_lock_irqsave(&pfc->lock, flags);
	val = sh_pfc_read(pfc, reg);
	spin_unlock_irqrestore(&pfc->lock, flags);

	val = (val >> offset) & GENMASK(size - 1, 0);

	/* Convert the value to mA based on a full drive strength value of 24mA.
	 * We can make the full value configurable later if needed.
	 */
	return (val + 1) * (size == 2 ? 6 : 3);
}