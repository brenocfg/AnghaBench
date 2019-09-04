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
struct sunxi_sid {scalar_t__ value_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  sunxi_sid_read_byte (struct sunxi_sid*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_sid_read(void *context, unsigned int offset,
			  void *val, size_t bytes)
{
	struct sunxi_sid *sid = context;
	u8 *buf = val;

	/* Offset the read operation to the real position of SID */
	offset += sid->value_offset;

	while (bytes--)
		*buf++ = sunxi_sid_read_byte(sid, offset++);

	return 0;
}