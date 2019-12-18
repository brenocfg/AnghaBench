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
typedef  void* u8 ;
struct wpan_phy {int dummy; } ;
struct wpan_dev {void* max_be; void* min_be; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 

__attribute__((used)) static int
ieee802154_set_backoff_exponent(struct wpan_phy *wpan_phy,
				struct wpan_dev *wpan_dev,
				u8 min_be, u8 max_be)
{
	ASSERT_RTNL();

	wpan_dev->min_be = min_be;
	wpan_dev->max_be = max_be;
	return 0;
}