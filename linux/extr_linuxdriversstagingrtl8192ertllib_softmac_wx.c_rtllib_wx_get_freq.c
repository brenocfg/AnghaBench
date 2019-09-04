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
struct iw_freq {int m; int e; } ;
union iwreq_data {struct iw_freq freq; } ;
struct TYPE_2__ {int channel; } ;
struct rtllib_device {TYPE_1__ current_network; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int* rtllib_wlan_frequencies ; 

int rtllib_wx_get_freq(struct rtllib_device *ieee,
			     struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	struct iw_freq *fwrq = &wrqu->freq;

	if (ieee->current_network.channel == 0)
		return -1;
	fwrq->m = rtllib_wlan_frequencies[ieee->current_network.channel-1] *
		  100000;
	fwrq->e = 1;
	return 0;
}