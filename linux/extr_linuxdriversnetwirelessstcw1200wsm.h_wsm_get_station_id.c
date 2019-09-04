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
typedef  int /*<<< orphan*/  u8 ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WSM_MIB_ID_DOT11_STATION_ID ; 
 int wsm_read_mib (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wsm_get_station_id(struct cw1200_common *priv, u8 *mac)
{
	return wsm_read_mib(priv, WSM_MIB_ID_DOT11_STATION_ID, mac, ETH_ALEN);
}