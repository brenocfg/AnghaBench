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
struct ds1343_priv {scalar_t__ alarm_sec; int irqen; scalar_t__ alarm_min; scalar_t__ alarm_hour; scalar_t__ alarm_mday; int /*<<< orphan*/  map; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int DS1343_A0IE ; 
 int /*<<< orphan*/  DS1343_ALM0_SEC_REG ; 
 int /*<<< orphan*/  DS1343_CONTROL_REG ; 
 unsigned int DS1343_IRQF0 ; 
 int /*<<< orphan*/  DS1343_STATUS_REG ; 
 int RTC_UF ; 
 int bin2bcd (scalar_t__) ; 
 struct ds1343_priv* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ds1343_update_alarm(struct device *dev)
{
	struct ds1343_priv *priv = dev_get_drvdata(dev);
	unsigned int control, stat;
	unsigned char buf[4];
	int res = 0;

	res = regmap_read(priv->map, DS1343_CONTROL_REG, &control);
	if (res)
		return res;

	res = regmap_read(priv->map, DS1343_STATUS_REG, &stat);
	if (res)
		return res;

	control &= ~(DS1343_A0IE);
	stat &= ~(DS1343_IRQF0);

	res = regmap_write(priv->map, DS1343_CONTROL_REG, control);
	if (res)
		return res;

	res = regmap_write(priv->map, DS1343_STATUS_REG, stat);
	if (res)
		return res;

	buf[0] = priv->alarm_sec < 0 || (priv->irqen & RTC_UF) ?
		0x80 : bin2bcd(priv->alarm_sec) & 0x7F;
	buf[1] = priv->alarm_min < 0 || (priv->irqen & RTC_UF) ?
		0x80 : bin2bcd(priv->alarm_min) & 0x7F;
	buf[2] = priv->alarm_hour < 0 || (priv->irqen & RTC_UF) ?
		0x80 : bin2bcd(priv->alarm_hour) & 0x3F;
	buf[3] = priv->alarm_mday < 0 || (priv->irqen & RTC_UF) ?
		0x80 : bin2bcd(priv->alarm_mday) & 0x7F;

	res = regmap_bulk_write(priv->map, DS1343_ALM0_SEC_REG, buf, 4);
	if (res)
		return res;

	if (priv->irqen) {
		control |= DS1343_A0IE;
		res = regmap_write(priv->map, DS1343_CONTROL_REG, control);
	}

	return res;
}