#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct airo_info {int /*<<< orphan*/  sem; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  Resp ;
typedef  TYPE_1__ Cmd ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ENABLED ; 
 int /*<<< orphan*/  MAC_DISABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issuecommand (struct airo_info*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_MAC( struct airo_info *ai, int lock ) {
        Cmd cmd;
	Resp rsp;

	if (lock == 1 && down_interruptible(&ai->sem))
		return;

	if (test_bit(FLAG_ENABLED, &ai->flags)) {
		if (lock != 2) /* lock == 2 means don't disable carrier */
			netif_carrier_off(ai->dev);
		memset(&cmd, 0, sizeof(cmd));
		cmd.cmd = MAC_DISABLE; // disable in case already enabled
		issuecommand(ai, &cmd, &rsp);
		clear_bit(FLAG_ENABLED, &ai->flags);
	}
	if (lock == 1)
		up(&ai->sem);
}