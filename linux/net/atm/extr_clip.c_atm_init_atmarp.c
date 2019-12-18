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
struct atm_vcc {int /*<<< orphan*/ * push_oam; int /*<<< orphan*/ * pop; int /*<<< orphan*/ * push; int /*<<< orphan*/ * dev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_META ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int CLIP_CHECK_INTERVAL ; 
 int EADDRINUSE ; 
 int HZ ; 
 struct atm_vcc* atmarpd ; 
 int /*<<< orphan*/  atmarpd_dev ; 
 int /*<<< orphan*/  idle_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  vcc_insert_socket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atm_init_atmarp(struct atm_vcc *vcc)
{
	rtnl_lock();
	if (atmarpd) {
		rtnl_unlock();
		return -EADDRINUSE;
	}

	mod_timer(&idle_timer, jiffies + CLIP_CHECK_INTERVAL * HZ);

	atmarpd = vcc;
	set_bit(ATM_VF_META, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);
	    /* allow replies and avoid getting closed if signaling dies */
	vcc->dev = &atmarpd_dev;
	vcc_insert_socket(sk_atm(vcc));
	vcc->push = NULL;
	vcc->pop = NULL; /* crash */
	vcc->push_oam = NULL; /* crash */
	rtnl_unlock();
	return 0;
}