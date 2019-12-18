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
struct mchp_i2s_mcc_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCHP_I2SMCC_SR ; 
 int MCHP_I2SMCC_SR_RXEN ; 
 int MCHP_I2SMCC_SR_TXEN ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mchp_i2s_mcc_is_running(struct mchp_i2s_mcc_dev *dev)
{
	u32 sr;

	regmap_read(dev->regmap, MCHP_I2SMCC_SR, &sr);
	return !!(sr & (MCHP_I2SMCC_SR_TXEN | MCHP_I2SMCC_SR_RXEN));
}