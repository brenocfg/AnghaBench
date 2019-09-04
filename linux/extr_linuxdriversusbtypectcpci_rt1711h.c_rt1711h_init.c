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
struct tcpci_data {int dummy; } ;
struct tcpci {int dummy; } ;
struct rt1711h_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT1711H_RTCTRL11 ; 
 int RT1711H_RTCTRL11_SET (int,int) ; 
 int /*<<< orphan*/  RT1711H_RTCTRL14 ; 
 int /*<<< orphan*/  RT1711H_RTCTRL15 ; 
 int /*<<< orphan*/  RT1711H_RTCTRL16 ; 
 int /*<<< orphan*/  RT1711H_RTCTRL8 ; 
 int RT1711H_RTCTRL8_SET (int /*<<< orphan*/ ,int,int,int) ; 
 int rt1711h_write16 (struct rt1711h_chip*,int /*<<< orphan*/ ,int) ; 
 int rt1711h_write8 (struct rt1711h_chip*,int /*<<< orphan*/ ,int) ; 
 struct rt1711h_chip* tdata_to_rt1711h (struct tcpci_data*) ; 

__attribute__((used)) static int rt1711h_init(struct tcpci *tcpci, struct tcpci_data *tdata)
{
	int ret;
	struct rt1711h_chip *chip = tdata_to_rt1711h(tdata);

	/* CK 300K from 320K, shipping off, auto_idle enable, tout = 32ms */
	ret = rt1711h_write8(chip, RT1711H_RTCTRL8,
			     RT1711H_RTCTRL8_SET(0, 1, 1, 2));
	if (ret < 0)
		return ret;

	/* I2C reset : (val + 1) * 12.5ms */
	ret = rt1711h_write8(chip, RT1711H_RTCTRL11,
			     RT1711H_RTCTRL11_SET(1, 0x0F));
	if (ret < 0)
		return ret;

	/* tTCPCfilter : (26.7 * val) us */
	ret = rt1711h_write8(chip, RT1711H_RTCTRL14, 0x0F);
	if (ret < 0)
		return ret;

	/*  tDRP : (51.2 + 6.4 * val) ms */
	ret = rt1711h_write8(chip, RT1711H_RTCTRL15, 0x04);
	if (ret < 0)
		return ret;

	/* dcSRC.DRP : 33% */
	return rt1711h_write16(chip, RT1711H_RTCTRL16, 330);
}