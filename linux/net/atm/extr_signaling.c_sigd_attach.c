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
struct atm_vcc {int /*<<< orphan*/  flags; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_META ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int EADDRINUSE ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct atm_vcc* sigd ; 
 int /*<<< orphan*/  sigd_dev ; 
 int /*<<< orphan*/  sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  vcc_insert_socket (int /*<<< orphan*/ ) ; 

int sigd_attach(struct atm_vcc *vcc)
{
	if (sigd)
		return -EADDRINUSE;
	pr_debug("\n");
	sigd = vcc;
	vcc->dev = &sigd_dev;
	vcc_insert_socket(sk_atm(vcc));
	set_bit(ATM_VF_META, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);
	return 0;
}