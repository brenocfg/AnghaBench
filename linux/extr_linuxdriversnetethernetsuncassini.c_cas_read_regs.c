#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cas {int /*<<< orphan*/  lock; scalar_t__ regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  cas_phy_read (struct cas*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ethtool_register_table ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cas_read_regs(struct cas *cp, u8 *ptr, int len)
{
	u8 *p;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&cp->lock, flags);
	for (i = 0, p = ptr; i < len ; i ++, p += sizeof(u32)) {
		u16 hval;
		u32 val;
		if (ethtool_register_table[i].offsets < 0) {
			hval = cas_phy_read(cp,
				    -ethtool_register_table[i].offsets);
			val = hval;
		} else {
			val= readl(cp->regs+ethtool_register_table[i].offsets);
		}
		memcpy(p, (u8 *)&val, sizeof(u32));
	}
	spin_unlock_irqrestore(&cp->lock, flags);
}