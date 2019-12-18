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
struct wpan_phy {int dummy; } ;
struct wpan_dev {int /*<<< orphan*/  frame_retries; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 

__attribute__((used)) static int
ieee802154_set_max_frame_retries(struct wpan_phy *wpan_phy,
				 struct wpan_dev *wpan_dev,
				 s8 max_frame_retries)
{
	ASSERT_RTNL();

	wpan_dev->frame_retries = max_frame_retries;
	return 0;
}