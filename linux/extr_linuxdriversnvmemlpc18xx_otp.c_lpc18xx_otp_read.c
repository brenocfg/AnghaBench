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
typedef  unsigned int u32 ;
struct lpc18xx_otp {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int LPC18XX_OTP_SIZE ; 
 int LPC18XX_OTP_WORD_SIZE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int lpc18xx_otp_read(void *context, unsigned int offset,
			    void *val, size_t bytes)
{
	struct lpc18xx_otp *otp = context;
	unsigned int count = bytes >> 2;
	u32 index = offset >> 2;
	u32 *buf = val;
	int i;

	if (count > (LPC18XX_OTP_SIZE - index))
		count = LPC18XX_OTP_SIZE - index;

	for (i = index; i < (index + count); i++)
		*buf++ = readl(otp->base + i * LPC18XX_OTP_WORD_SIZE);

	return 0;
}