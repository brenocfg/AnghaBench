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
union iwreq_data {int /*<<< orphan*/  mode; } ;
struct rtllib_device {int /*<<< orphan*/  iw_mode; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */

int rtllib_wx_get_mode(struct rtllib_device *ieee, struct iw_request_info *a,
		       union iwreq_data *wrqu, char *b)
{
	wrqu->mode = ieee->iw_mode;
	return 0;
}