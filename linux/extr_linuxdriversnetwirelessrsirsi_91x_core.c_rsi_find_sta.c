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
struct rsi_sta {TYPE_1__* sta; } ;
struct rsi_common {int max_stations; struct rsi_sta* stations; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct rsi_sta *rsi_find_sta(struct rsi_common *common, u8 *mac_addr)
{
	int i;

	for (i = 0; i < common->max_stations; i++) {
		if (!common->stations[i].sta)
			continue;
		if (!(memcmp(common->stations[i].sta->addr,
			     mac_addr, ETH_ALEN)))
			return &common->stations[i];
	}
	return NULL;
}