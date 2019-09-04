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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct snvs_rtc_data {TYPE_1__* rtc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CNTR_TO_SECS_SH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int rtc_read_lpsrt (struct snvs_rtc_data*) ; 

__attribute__((used)) static u32 rtc_read_lp_counter(struct snvs_rtc_data *data)
{
	u64 read1, read2;
	unsigned int timeout = 100;

	/* As expected, the registers might update between the read of the LSB
	 * reg and the MSB reg.  It's also possible that one register might be
	 * in partially modified state as well.
	 */
	read1 = rtc_read_lpsrt(data);
	do {
		read2 = read1;
		read1 = rtc_read_lpsrt(data);
	} while (read1 != read2 && --timeout);
	if (!timeout)
		dev_err(&data->rtc->dev, "Timeout trying to get valid LPSRT Counter read\n");

	/* Convert 47-bit counter to 32-bit raw second count */
	return (u32) (read1 >> CNTR_TO_SECS_SH);
}