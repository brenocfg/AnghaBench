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
struct device {int dummy; } ;
struct asm9260_rtc_priv {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_AMR_OFF ; 
 scalar_t__ HW_AMR ; 
 struct asm9260_rtc_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int asm9260_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct asm9260_rtc_priv *priv = dev_get_drvdata(dev);

	iowrite32(enabled ? 0 : BM_AMR_OFF, priv->iobase + HW_AMR);
	return 0;
}