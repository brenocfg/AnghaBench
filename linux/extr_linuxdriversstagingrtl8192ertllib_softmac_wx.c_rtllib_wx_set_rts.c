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
struct TYPE_2__ {scalar_t__ value; int /*<<< orphan*/  fixed; scalar_t__ disabled; } ;
union iwreq_data {TYPE_1__ rts; } ;
struct rtllib_device {scalar_t__ rts; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_RTS_THRESHOLD ; 
 int EINVAL ; 
 scalar_t__ MAX_RTS_THRESHOLD ; 
 scalar_t__ MIN_RTS_THRESHOLD ; 

int rtllib_wx_set_rts(struct rtllib_device *ieee,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	if (wrqu->rts.disabled || !wrqu->rts.fixed)
		ieee->rts = DEFAULT_RTS_THRESHOLD;
	else {
		if (wrqu->rts.value < MIN_RTS_THRESHOLD ||
				wrqu->rts.value > MAX_RTS_THRESHOLD)
			return -EINVAL;
		ieee->rts = wrqu->rts.value;
	}
	return 0;
}