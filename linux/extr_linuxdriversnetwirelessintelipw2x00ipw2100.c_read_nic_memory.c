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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_REG_AUTOINCREMENT_ADDRESS ; 
 int /*<<< orphan*/  IPW_REG_AUTOINCREMENT_DATA ; 
 int /*<<< orphan*/  IPW_REG_INDIRECT_ACCESS_ADDRESS ; 
 scalar_t__ IPW_REG_INDIRECT_ACCESS_DATA ; 
 int /*<<< orphan*/  read_register (struct net_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  read_register_byte (struct net_device*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_register (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void read_nic_memory(struct net_device *dev, u32 addr, u32 len,
				   u8 * buf)
{
	u32 aligned_addr;
	u32 aligned_len;
	u32 dif_len;
	u32 i;

	/* read first nibble byte by byte */
	aligned_addr = addr & (~0x3);
	dif_len = addr - aligned_addr;
	if (dif_len) {
		/* Start reading at aligned_addr + dif_len */
		write_register(dev, IPW_REG_INDIRECT_ACCESS_ADDRESS,
			       aligned_addr);
		for (i = dif_len; i < 4; i++, buf++)
			read_register_byte(dev,
					   IPW_REG_INDIRECT_ACCESS_DATA + i,
					   buf);

		len -= dif_len;
		aligned_addr += 4;
	}

	/* read DWs through autoincrement registers */
	write_register(dev, IPW_REG_AUTOINCREMENT_ADDRESS, aligned_addr);
	aligned_len = len & (~0x3);
	for (i = 0; i < aligned_len; i += 4, buf += 4, aligned_addr += 4)
		read_register(dev, IPW_REG_AUTOINCREMENT_DATA, (u32 *) buf);

	/* copy the last nibble */
	dif_len = len - aligned_len;
	write_register(dev, IPW_REG_INDIRECT_ACCESS_ADDRESS, aligned_addr);
	for (i = 0; i < dif_len; i++, buf++)
		read_register_byte(dev, IPW_REG_INDIRECT_ACCESS_DATA + i, buf);
}