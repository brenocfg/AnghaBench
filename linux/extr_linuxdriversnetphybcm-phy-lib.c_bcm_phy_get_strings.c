#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct phy_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int ETH_GSTRING_LEN ; 
 TYPE_1__* bcm_phy_hw_stats ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

void bcm_phy_get_strings(struct phy_device *phydev, u8 *data)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(bcm_phy_hw_stats); i++)
		strlcpy(data + i * ETH_GSTRING_LEN,
			bcm_phy_hw_stats[i].string, ETH_GSTRING_LEN);
}