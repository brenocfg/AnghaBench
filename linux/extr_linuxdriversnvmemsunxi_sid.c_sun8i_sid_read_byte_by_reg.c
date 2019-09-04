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
typedef  unsigned int u8 ;
typedef  unsigned int const u32 ;
struct sunxi_sid {int dummy; } ;

/* Variables and functions */
 int sun8i_sid_register_readout (struct sunxi_sid const*,unsigned int const,unsigned int const*) ; 

__attribute__((used)) static int sun8i_sid_read_byte_by_reg(const struct sunxi_sid *sid,
				      const unsigned int offset,
				      u8 *out)
{
	u32 word;
	int ret;

	ret = sun8i_sid_register_readout(sid, offset & ~0x03, &word);

	if (ret)
		return ret;

	*out = (word >> ((offset & 0x3) * 8)) & 0xff;

	return 0;
}