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
typedef  int /*<<< orphan*/  u32 ;
struct omap_rtc {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* lock ) (struct omap_rtc*) ;int /*<<< orphan*/  (* unlock ) (struct omap_rtc*) ;} ;

/* Variables and functions */
 scalar_t__ OMAP_RTC_SCRATCH0_REG ; 
 int /*<<< orphan*/  rtc_writel (struct omap_rtc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_rtc*) ; 
 int /*<<< orphan*/  stub2 (struct omap_rtc*) ; 

__attribute__((used)) static int omap_rtc_scratch_write(void *priv, unsigned int offset, void *_val,
				  size_t bytes)
{
	struct omap_rtc	*rtc = priv;
	u32 *val = _val;
	int i;

	rtc->type->unlock(rtc);
	for (i = 0; i < bytes / 4; i++)
		rtc_writel(rtc,
			   OMAP_RTC_SCRATCH0_REG + offset + (i * 4), val[i]);
	rtc->type->lock(rtc);

	return 0;
}