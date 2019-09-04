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
struct rt2x00_dev {int /*<<< orphan*/  csr_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_CSR_CFG0 ; 
 int /*<<< orphan*/  RF_CSR_CFG0_BUSY ; 
 int /*<<< orphan*/  RF_CSR_CFG0_REG_VALUE_BW ; 
 int /*<<< orphan*/  RF_CSR_CFG0_SEL ; 
 int /*<<< orphan*/  RF_CSR_CFG0_STANDBYMODE ; 
 scalar_t__ WAIT_FOR_RF (struct rt2x00_dev*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write_lock (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_rf_write (struct rt2x00_dev*,unsigned int const,int const) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void rt2800_rf_write(struct rt2x00_dev *rt2x00dev,
			    const unsigned int word, const u32 value)
{
	u32 reg;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the RF becomes available, afterwards we
	 * can safely write the new data into the register.
	 */
	if (WAIT_FOR_RF(rt2x00dev, &reg)) {
		reg = 0;
		rt2x00_set_field32(&reg, RF_CSR_CFG0_REG_VALUE_BW, value);
		rt2x00_set_field32(&reg, RF_CSR_CFG0_STANDBYMODE, 0);
		rt2x00_set_field32(&reg, RF_CSR_CFG0_SEL, 0);
		rt2x00_set_field32(&reg, RF_CSR_CFG0_BUSY, 1);

		rt2800_register_write_lock(rt2x00dev, RF_CSR_CFG0, reg);
		rt2x00_rf_write(rt2x00dev, word, value);
	}

	mutex_unlock(&rt2x00dev->csr_mutex);
}