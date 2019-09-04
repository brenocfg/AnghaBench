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

/* Variables and functions */
 unsigned char EC_WLAN_ENTER_RESET ; 
 unsigned char EC_WLAN_LEAVE_RESET ; 
 int card_blocked ; 
 int olpc_ec_cmd (unsigned char,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfkill_set_block(void *data, bool blocked)
{
	unsigned char cmd;
	int r;

	if (blocked == card_blocked)
		return 0;

	if (blocked)
		cmd = EC_WLAN_ENTER_RESET;
	else
		cmd = EC_WLAN_LEAVE_RESET;

	r = olpc_ec_cmd(cmd, NULL, 0, NULL, 0);
	if (r == 0)
		card_blocked = blocked;

	return r;
}