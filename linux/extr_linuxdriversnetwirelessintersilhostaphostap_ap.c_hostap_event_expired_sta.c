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
typedef  int /*<<< orphan*/  wrqu ;
struct TYPE_2__ {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
union iwreq_data {TYPE_1__ addr; } ;
struct sta_info {int /*<<< orphan*/  addr; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IWEVEXPIRED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hostap_event_expired_sta(struct net_device *dev,
				     struct sta_info *sta)
{
	union iwreq_data wrqu;
	memset(&wrqu, 0, sizeof(wrqu));
	memcpy(wrqu.addr.sa_data, sta->addr, ETH_ALEN);
	wrqu.addr.sa_family = ARPHRD_ETHER;
	wireless_send_event(dev, IWEVEXPIRED, &wrqu, NULL);
}