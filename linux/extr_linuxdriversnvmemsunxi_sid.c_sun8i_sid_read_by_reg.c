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
struct sunxi_sid {int dummy; } ;

/* Variables and functions */
 int sun8i_sid_read_byte_by_reg (struct sunxi_sid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun8i_sid_read_by_reg(void *context, unsigned int offset,
				 void *val, size_t bytes)
{
	struct sunxi_sid *sid = context;
	u8 *buf = val;
	int ret;

	while (bytes--) {
		ret = sun8i_sid_read_byte_by_reg(sid, offset++, buf++);
		if (ret)
			return ret;
	}

	return 0;
}