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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int i2c_master_send (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  put_unaligned_be16 (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sigmadsp_write_i2c(void *control_data,
	unsigned int addr, const uint8_t data[], size_t len)
{
	uint8_t *buf;
	int ret;

	buf = kzalloc(2 + len, GFP_KERNEL | GFP_DMA);
	if (!buf)
		return -ENOMEM;

	put_unaligned_be16(addr, buf);
	memcpy(buf + 2, data, len);

	ret = i2c_master_send(control_data, buf, len + 2);

	kfree(buf);

	if (ret < 0)
		return ret;

	return 0;
}