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
struct ds3232 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS3232_REG_CR ; 
 int DS3232_REG_CR_A1IE ; 
 int DS3232_REG_CR_A2IE ; 
 int DS3232_REG_CR_INTCN ; 
 int /*<<< orphan*/  DS3232_REG_SR ; 
 int DS3232_REG_SR_A1F ; 
 int DS3232_REG_SR_A2F ; 
 int DS3232_REG_SR_OSF ; 
 struct ds3232* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds3232_check_rtc_status(struct device *dev)
{
	struct ds3232 *ds3232 = dev_get_drvdata(dev);
	int ret = 0;
	int control, stat;

	ret = regmap_read(ds3232->regmap, DS3232_REG_SR, &stat);
	if (ret)
		return ret;

	if (stat & DS3232_REG_SR_OSF)
		dev_warn(dev,
				"oscillator discontinuity flagged, "
				"time unreliable\n");

	stat &= ~(DS3232_REG_SR_OSF | DS3232_REG_SR_A1F | DS3232_REG_SR_A2F);

	ret = regmap_write(ds3232->regmap, DS3232_REG_SR, stat);
	if (ret)
		return ret;

	/* If the alarm is pending, clear it before requesting
	 * the interrupt, so an interrupt event isn't reported
	 * before everything is initialized.
	 */

	ret = regmap_read(ds3232->regmap, DS3232_REG_CR, &control);
	if (ret)
		return ret;

	control &= ~(DS3232_REG_CR_A1IE | DS3232_REG_CR_A2IE);
	control |= DS3232_REG_CR_INTCN;

	return regmap_write(ds3232->regmap, DS3232_REG_CR, control);
}