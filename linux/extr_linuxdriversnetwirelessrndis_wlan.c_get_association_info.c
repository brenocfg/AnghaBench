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
struct usbnet {int dummy; } ;
struct ndis_80211_assoc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_OID_802_11_ASSOCIATION_INFORMATION ; 
 int rndis_query_oid (struct usbnet*,int /*<<< orphan*/ ,struct ndis_80211_assoc_info*,int*) ; 

__attribute__((used)) static int get_association_info(struct usbnet *usbdev,
			struct ndis_80211_assoc_info *info, int len)
{
	return rndis_query_oid(usbdev,
			RNDIS_OID_802_11_ASSOCIATION_INFORMATION,
			info, &len);
}