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
struct ieee802154_hw {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC2520_CMD_SRXON ; 
 int cc2520_cmd_strobe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc2520_start(struct ieee802154_hw *hw)
{
	return cc2520_cmd_strobe(hw->priv, CC2520_CMD_SRXON);
}