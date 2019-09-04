#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct TYPE_2__ {int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; int /*<<< orphan*/  pending; } ;
struct ds1307 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 unsigned char DS1337_BIT_A1I ; 
 unsigned char DS1337_BIT_A1IE ; 
 unsigned char DS1337_BIT_A2I ; 
 unsigned char DS1337_BIT_A2IE ; 
 int /*<<< orphan*/  DS1337_REG_CONTROL ; 
 int /*<<< orphan*/  DS1339_REG_ALARM1_SECS ; 
 int EINVAL ; 
 int /*<<< orphan*/  HAS_ALARM ; 
 unsigned char bin2bcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct ds1307* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1337_set_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct ds1307		*ds1307 = dev_get_drvdata(dev);
	unsigned char		regs[9];
	u8			control, status;
	int			ret;

	if (!test_bit(HAS_ALARM, &ds1307->flags))
		return -EINVAL;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, enabled=%d, pending=%d\n",
		"alarm set", t->time.tm_sec, t->time.tm_min,
		t->time.tm_hour, t->time.tm_mday,
		t->enabled, t->pending);

	/* read current status of both alarms and the chip */
	ret = regmap_bulk_read(ds1307->regmap, DS1339_REG_ALARM1_SECS, regs,
			       sizeof(regs));
	if (ret) {
		dev_err(dev, "%s error %d\n", "alarm write", ret);
		return ret;
	}
	control = regs[7];
	status = regs[8];

	dev_dbg(dev, "%s: %4ph, %3ph, %02x %02x\n", "alarm set (old status)",
		&regs[0], &regs[4], control, status);

	/* set ALARM1, using 24 hour and day-of-month modes */
	regs[0] = bin2bcd(t->time.tm_sec);
	regs[1] = bin2bcd(t->time.tm_min);
	regs[2] = bin2bcd(t->time.tm_hour);
	regs[3] = bin2bcd(t->time.tm_mday);

	/* set ALARM2 to non-garbage */
	regs[4] = 0;
	regs[5] = 0;
	regs[6] = 0;

	/* disable alarms */
	regs[7] = control & ~(DS1337_BIT_A1IE | DS1337_BIT_A2IE);
	regs[8] = status & ~(DS1337_BIT_A1I | DS1337_BIT_A2I);

	ret = regmap_bulk_write(ds1307->regmap, DS1339_REG_ALARM1_SECS, regs,
				sizeof(regs));
	if (ret) {
		dev_err(dev, "can't set alarm time\n");
		return ret;
	}

	/* optionally enable ALARM1 */
	if (t->enabled) {
		dev_dbg(dev, "alarm IRQ armed\n");
		regs[7] |= DS1337_BIT_A1IE;	/* only ALARM1 is used */
		regmap_write(ds1307->regmap, DS1337_REG_CONTROL, regs[7]);
	}

	return 0;
}