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
typedef  int u32 ;
struct mt76x0_dev {int dummy; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  mt76x0_burst_write_regs (struct mt76x0_dev*,int,void const*,int) ; 

__attribute__((used)) static void mt76x0_wr_copy(struct mt76_dev *dev, u32 offset,
			   const void *data, int len)
{
	WARN_ONCE(offset & 3, "unaligned write copy off:%08x", offset);
	WARN_ONCE(len & 3, "short write copy off:%08x", offset);

	mt76x0_burst_write_regs((struct mt76x0_dev *) dev, offset, data, len / 4);
}