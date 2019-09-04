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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct iw_thrspy {int /*<<< orphan*/  low; } ;
struct iw_spy_data {int /*<<< orphan*/  spy_thr_under; int /*<<< orphan*/  spy_thr_low; } ;
struct iw_request_info {int dummy; } ;
struct iw_quality {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct iw_spy_data* get_spydata (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 

int iw_handler_set_thrspy(struct net_device *	dev,
			  struct iw_request_info *info,
			  union iwreq_data *	wrqu,
			  char *		extra)
{
	struct iw_spy_data *	spydata = get_spydata(dev);
	struct iw_thrspy *	threshold = (struct iw_thrspy *) extra;

	/* Make sure driver is not buggy or using the old API */
	if (!spydata)
		return -EOPNOTSUPP;

	/* Just do it */
	memcpy(&(spydata->spy_thr_low), &(threshold->low),
	       2 * sizeof(struct iw_quality));

	/* Clear flag */
	memset(spydata->spy_thr_under, '\0', sizeof(spydata->spy_thr_under));

	return 0;
}