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
typedef  int /*<<< orphan*/  u8 ;
struct rtllib_device {TYPE_1__* PMKIDList; } ;
struct TYPE_2__ {int /*<<< orphan*/  Bssid; scalar_t__ bUsed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int NUM_PMKID_CACHE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int SecIsInPMKIDList(struct rtllib_device *ieee, u8 *bssid)
{
	int i = 0;

	do {
		if ((ieee->PMKIDList[i].bUsed) &&
		   (memcmp(ieee->PMKIDList[i].Bssid, bssid, ETH_ALEN) == 0))
			break;
		i++;
	} while (i < NUM_PMKID_CACHE);

	if (i == NUM_PMKID_CACHE)
		i = -1;
	return i;
}