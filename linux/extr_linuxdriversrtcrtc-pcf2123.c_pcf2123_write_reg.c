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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  txbuf ;
struct device {int dummy; } ;

/* Variables and functions */
 int pcf2123_write (struct device*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pcf2123_write_reg(struct device *dev, u8 reg, u8 val)
{
	u8 txbuf[2];

	txbuf[0] = reg;
	txbuf[1] = val;
	return pcf2123_write(dev, txbuf, sizeof(txbuf));
}