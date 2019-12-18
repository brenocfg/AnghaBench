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
struct l3_pins {int /*<<< orphan*/  (* setmode ) (struct l3_pins*,int) ;int /*<<< orphan*/  (* setdat ) (struct l3_pins*,int) ;int /*<<< orphan*/  (* setclk ) (struct l3_pins*,int) ;int /*<<< orphan*/  mode_hold; int /*<<< orphan*/  mode_setup; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  sendbyte (struct l3_pins*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendbytes (struct l3_pins*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct l3_pins*,int) ; 
 int /*<<< orphan*/  stub2 (struct l3_pins*,int) ; 
 int /*<<< orphan*/  stub3 (struct l3_pins*,int) ; 
 int /*<<< orphan*/  stub4 (struct l3_pins*,int) ; 
 int /*<<< orphan*/  stub5 (struct l3_pins*,int) ; 
 int /*<<< orphan*/  stub6 (struct l3_pins*,int) ; 
 int /*<<< orphan*/  stub7 (struct l3_pins*,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

int l3_write(struct l3_pins *adap, u8 addr, u8 *data, int len)
{
	adap->setclk(adap, 1);
	adap->setdat(adap, 1);
	adap->setmode(adap, 1);
	udelay(adap->mode);

	adap->setmode(adap, 0);
	udelay(adap->mode_setup);
	sendbyte(adap, addr);
	udelay(adap->mode_hold);

	sendbytes(adap, data, len);

	adap->setclk(adap, 1);
	adap->setdat(adap, 1);
	adap->setmode(adap, 0);

	return len;
}