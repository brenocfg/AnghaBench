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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hdq_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ OMAP_HDQ_FLAG_CLEAR ; 
 scalar_t__ OMAP_HDQ_FLAG_SET ; 
 unsigned long OMAP_HDQ_TIMEOUT ; 
 scalar_t__ hdq_reg_in (struct hdq_data*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int hdq_wait_for_flag(struct hdq_data *hdq_data, u32 offset,
		u8 flag, u8 flag_set, u8 *status)
{
	int ret = 0;
	unsigned long timeout = jiffies + OMAP_HDQ_TIMEOUT;

	if (flag_set == OMAP_HDQ_FLAG_CLEAR) {
		/* wait for the flag clear */
		while (((*status = hdq_reg_in(hdq_data, offset)) & flag)
			&& time_before(jiffies, timeout)) {
			schedule_timeout_uninterruptible(1);
		}
		if (*status & flag)
			ret = -ETIMEDOUT;
	} else if (flag_set == OMAP_HDQ_FLAG_SET) {
		/* wait for the flag set */
		while (!((*status = hdq_reg_in(hdq_data, offset)) & flag)
			&& time_before(jiffies, timeout)) {
			schedule_timeout_uninterruptible(1);
		}
		if (!(*status & flag))
			ret = -ETIMEDOUT;
	} else
		return -EINVAL;

	return ret;
}