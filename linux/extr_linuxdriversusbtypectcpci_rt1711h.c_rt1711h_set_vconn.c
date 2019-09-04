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
 int /*<<< orphan*/  RT1711H_RTCTRL8 ; 
 int /*<<< orphan*/  RT1711H_RTCTRL8_SET (int /*<<< orphan*/ ,int,int,int) ; 
 int rt1711h_write8 (struct rt1711h_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rt1711h_chip* tdata_to_rt1711h (struct tcpci_data*) ; 

__attribute__((used)) static int rt1711h_set_vconn(struct tcpci *tcpci, struct tcpci_data *tdata,
			     bool enable)
{
	struct rt1711h_chip *chip = tdata_to_rt1711h(tdata);

	return rt1711h_write8(chip, RT1711H_RTCTRL8,
			      RT1711H_RTCTRL8_SET(0, 1, !enable, 2));
}