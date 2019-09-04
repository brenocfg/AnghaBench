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
typedef  int u8 ;
typedef  int u32 ;
struct arcxcnn {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCXCNN_WLED_ISET_LSB ; 
 int ARCXCNN_WLED_ISET_LSB_SHIFT ; 
 int /*<<< orphan*/  ARCXCNN_WLED_ISET_MSB ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int arcxcnn_set_brightness(struct arcxcnn *lp, u32 brightness)
{
	int ret;
	u8 val;

	/* lower nibble of brightness goes in upper nibble of LSB register */
	val = (brightness & 0xF) << ARCXCNN_WLED_ISET_LSB_SHIFT;
	ret = i2c_smbus_write_byte_data(lp->client,
		ARCXCNN_WLED_ISET_LSB, val);
	if (ret < 0)
		return ret;

	/* remaining 8 bits of brightness go in MSB register */
	val = (brightness >> 4);
	return i2c_smbus_write_byte_data(lp->client,
		ARCXCNN_WLED_ISET_MSB, val);
}