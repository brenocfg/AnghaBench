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
struct rtc7301_priv {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RTC7301_CONTROL ; 
 int RTC7301_CONTROL_BUSY ; 
 int rtc7301_read (struct rtc7301_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rtc7301_wait_while_busy(struct rtc7301_priv *priv)
{
	int retries = 100;

	while (retries-- > 0) {
		u8 val;

		val = rtc7301_read(priv, RTC7301_CONTROL);
		if (!(val & RTC7301_CONTROL_BUSY))
			return 0;

		udelay(300);
	}

	return -ETIMEDOUT;
}