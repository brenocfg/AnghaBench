#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {unsigned long sec; scalar_t__ nsec; } ;
struct TYPE_4__ {int sec; int nsec; } ;
struct TYPE_6__ {TYPE_2__ period; TYPE_1__ start; } ;
struct ptp_clock_request {TYPE_3__ perout; } ;
struct phy_device {int dummy; } ;
struct dp83640_private {struct phy_device* phydev; } ;
struct dp83640_clock {int /*<<< orphan*/  extreg_lock; int /*<<< orphan*/  ptp_clock; struct dp83640_private* chosen; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PAGE4 ; 
 int /*<<< orphan*/  PAGE5 ; 
 int /*<<< orphan*/  PTP_CTL ; 
 int /*<<< orphan*/  PTP_PF_PEROUT ; 
 int /*<<< orphan*/  PTP_TDR ; 
 int /*<<< orphan*/  PTP_TRIG ; 
 int TRIG_CSEL_MASK ; 
 int TRIG_CSEL_SHIFT ; 
 int TRIG_DIS ; 
 int TRIG_EN ; 
 int TRIG_GPIO_MASK ; 
 int TRIG_GPIO_SHIFT ; 
 int TRIG_LOAD ; 
 int TRIG_PER ; 
 int TRIG_PULSE ; 
 int TRIG_SEL_MASK ; 
 int TRIG_SEL_SHIFT ; 
 int TRIG_WR ; 
 int /*<<< orphan*/  ext_write (int /*<<< orphan*/ ,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ptp_find_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int periodic_output(struct dp83640_clock *clock,
			   struct ptp_clock_request *clkreq, bool on,
			   int trigger)
{
	struct dp83640_private *dp83640 = clock->chosen;
	struct phy_device *phydev = dp83640->phydev;
	u32 sec, nsec, pwidth;
	u16 gpio, ptp_trig, val;

	if (on) {
		gpio = 1 + ptp_find_pin(clock->ptp_clock, PTP_PF_PEROUT,
					trigger);
		if (gpio < 1)
			return -EINVAL;
	} else {
		gpio = 0;
	}

	ptp_trig = TRIG_WR |
		(trigger & TRIG_CSEL_MASK) << TRIG_CSEL_SHIFT |
		(gpio & TRIG_GPIO_MASK) << TRIG_GPIO_SHIFT |
		TRIG_PER |
		TRIG_PULSE;

	val = (trigger & TRIG_SEL_MASK) << TRIG_SEL_SHIFT;

	if (!on) {
		val |= TRIG_DIS;
		mutex_lock(&clock->extreg_lock);
		ext_write(0, phydev, PAGE5, PTP_TRIG, ptp_trig);
		ext_write(0, phydev, PAGE4, PTP_CTL, val);
		mutex_unlock(&clock->extreg_lock);
		return 0;
	}

	sec = clkreq->perout.start.sec;
	nsec = clkreq->perout.start.nsec;
	pwidth = clkreq->perout.period.sec * 1000000000UL;
	pwidth += clkreq->perout.period.nsec;
	pwidth /= 2;

	mutex_lock(&clock->extreg_lock);

	ext_write(0, phydev, PAGE5, PTP_TRIG, ptp_trig);

	/*load trigger*/
	val |= TRIG_LOAD;
	ext_write(0, phydev, PAGE4, PTP_CTL, val);
	ext_write(0, phydev, PAGE4, PTP_TDR, nsec & 0xffff);   /* ns[15:0] */
	ext_write(0, phydev, PAGE4, PTP_TDR, nsec >> 16);      /* ns[31:16] */
	ext_write(0, phydev, PAGE4, PTP_TDR, sec & 0xffff);    /* sec[15:0] */
	ext_write(0, phydev, PAGE4, PTP_TDR, sec >> 16);       /* sec[31:16] */
	ext_write(0, phydev, PAGE4, PTP_TDR, pwidth & 0xffff); /* ns[15:0] */
	ext_write(0, phydev, PAGE4, PTP_TDR, pwidth >> 16);    /* ns[31:16] */
	/* Triggers 0 and 1 has programmable pulsewidth2 */
	if (trigger < 2) {
		ext_write(0, phydev, PAGE4, PTP_TDR, pwidth & 0xffff);
		ext_write(0, phydev, PAGE4, PTP_TDR, pwidth >> 16);
	}

	/*enable trigger*/
	val &= ~TRIG_LOAD;
	val |= TRIG_EN;
	ext_write(0, phydev, PAGE4, PTP_CTL, val);

	mutex_unlock(&clock->extreg_lock);
	return 0;
}