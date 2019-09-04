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
union iwreq_data {int /*<<< orphan*/  name; } ;
struct rtllib_device {int modulation; int mode; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int IEEE_N_24G ; 
 int IEEE_N_5G ; 
 int RTLLIB_CCK_MODULATION ; 
 int RTLLIB_OFDM_MODULATION ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int rtllib_wx_get_name(struct rtllib_device *ieee,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	strcpy(wrqu->name, "802.11");

	if (ieee->modulation & RTLLIB_CCK_MODULATION)
		strcat(wrqu->name, "b");
	if (ieee->modulation & RTLLIB_OFDM_MODULATION)
		strcat(wrqu->name, "g");
	if (ieee->mode & (IEEE_N_24G | IEEE_N_5G))
		strcat(wrqu->name, "n");
	return 0;
}