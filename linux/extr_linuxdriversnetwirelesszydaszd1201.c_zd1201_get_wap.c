#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int updated; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {TYPE_1__ qual; } ;
struct zd1201 {TYPE_2__ iwstats; } ;
struct sockaddr {unsigned char* sa_data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ZD1201_RID_COMMSQUALITY ; 
 int /*<<< orphan*/  ZD1201_RID_CURRENTBSSID ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int zd1201_getconfig (struct zd1201*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int zd1201_get_wap(struct net_device *dev,
    struct iw_request_info *info, struct sockaddr *ap_addr, char *extra)
{
	struct zd1201 *zd = netdev_priv(dev);
	unsigned char buffer[6];

	if (!zd1201_getconfig(zd, ZD1201_RID_COMMSQUALITY, buffer, 6)) {
		/* Unfortunately the quality and noise reported is useless.
		   they seem to be accumulators that increase until you
		   read them, unless we poll on a fixed interval we can't
		   use them
		 */
		/*zd->iwstats.qual.qual = le16_to_cpu(((__le16 *)buffer)[0]);*/
		zd->iwstats.qual.level = le16_to_cpu(((__le16 *)buffer)[1]);
		/*zd->iwstats.qual.noise = le16_to_cpu(((__le16 *)buffer)[2]);*/
		zd->iwstats.qual.updated = 2;
	}

	return zd1201_getconfig(zd, ZD1201_RID_CURRENTBSSID, ap_addr->sa_data, 6);
}