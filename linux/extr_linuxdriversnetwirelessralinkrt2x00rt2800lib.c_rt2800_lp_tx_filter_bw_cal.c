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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int rt2800_bbp_dcoc_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_bbp_dcoc_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int rt2800_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static char rt2800_lp_tx_filter_bw_cal(struct rt2x00_dev *rt2x00dev)
{
	unsigned int cnt;
	u8 bbp_val;
	char cal_val;

	rt2800_bbp_dcoc_write(rt2x00dev, 0, 0x82);

	cnt = 0;
	do {
		usleep_range(500, 2000);
		bbp_val = rt2800_bbp_read(rt2x00dev, 159);
		if (bbp_val == 0x02 || cnt == 20)
			break;

		cnt++;
	} while (cnt < 20);

	bbp_val = rt2800_bbp_dcoc_read(rt2x00dev, 0x39);
	cal_val = bbp_val & 0x7F;
	if (cal_val >= 0x40)
		cal_val -= 128;

	return cal_val;
}