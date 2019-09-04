#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tb {TYPE_1__* root_switch; int /*<<< orphan*/  dev; } ;
struct icm {int /*<<< orphan*/  rpm; scalar_t__ safe_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  rpm; int /*<<< orphan*/  no_nvm_upgrade; } ;

/* Variables and functions */
 int ENODEV ; 
 struct icm* tb_priv (struct tb*) ; 
 int tb_switch_add (TYPE_1__*) ; 
 TYPE_1__* tb_switch_alloc (struct tb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* tb_switch_alloc_safe_mode (struct tb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_switch_put (TYPE_1__*) ; 
 int /*<<< orphan*/  x86_apple_machine ; 

__attribute__((used)) static int icm_start(struct tb *tb)
{
	struct icm *icm = tb_priv(tb);
	int ret;

	if (icm->safe_mode)
		tb->root_switch = tb_switch_alloc_safe_mode(tb, &tb->dev, 0);
	else
		tb->root_switch = tb_switch_alloc(tb, &tb->dev, 0);
	if (!tb->root_switch)
		return -ENODEV;

	/*
	 * NVM upgrade has not been tested on Apple systems and they
	 * don't provide images publicly either. To be on the safe side
	 * prevent root switch NVM upgrade on Macs for now.
	 */
	tb->root_switch->no_nvm_upgrade = x86_apple_machine;
	tb->root_switch->rpm = icm->rpm;

	ret = tb_switch_add(tb->root_switch);
	if (ret) {
		tb_switch_put(tb->root_switch);
		tb->root_switch = NULL;
	}

	return ret;
}