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
typedef  int u8 ;
typedef  int u32 ;
struct yenta_socket {int flags; } ;
struct TYPE_3__ {int Vcc; int Vpp; } ;
typedef  TYPE_1__ socket_state_t ;

/* Variables and functions */
 int CB_CBCARD ; 
 int CB_SC_VCC_3V ; 
 int CB_SC_VCC_5V ; 
 int CB_SC_VPP_12V ; 
 int CB_SC_VPP_3V ; 
 int CB_SC_VPP_5V ; 
 int /*<<< orphan*/  CB_SOCKET_CONTROL ; 
 int /*<<< orphan*/  CB_SOCKET_STATE ; 
 int /*<<< orphan*/  I365_POWER ; 
 int I365_VCC_3V ; 
 int I365_VCC_5V ; 
 int I365_VCC_MASK ; 
 int I365_VPP1_12V ; 
 int I365_VPP1_5V ; 
 int I365_VPP1_MASK ; 
 int I365_VPP2_12V ; 
 int I365_VPP2_5V ; 
 int I365_VPP2_MASK ; 
 int YENTA_16BIT_POWER_DF ; 
 int YENTA_16BIT_POWER_EXCA ; 
 int cb_readl (struct yenta_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb_writel (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 
 int exca_readb (struct yenta_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_writeb (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void yenta_set_power(struct yenta_socket *socket, socket_state_t *state)
{
	/* some birdges require to use the ExCA registers to power 16bit cards */
	if (!(cb_readl(socket, CB_SOCKET_STATE) & CB_CBCARD) &&
	    (socket->flags & YENTA_16BIT_POWER_EXCA)) {
		u8 reg, old;
		reg = old = exca_readb(socket, I365_POWER);
		reg &= ~(I365_VCC_MASK | I365_VPP1_MASK | I365_VPP2_MASK);

		/* i82365SL-DF style */
		if (socket->flags & YENTA_16BIT_POWER_DF) {
			switch (state->Vcc) {
			case 33:
				reg |= I365_VCC_3V;
				break;
			case 50:
				reg |= I365_VCC_5V;
				break;
			default:
				reg = 0;
				break;
			}
			switch (state->Vpp) {
			case 33:
			case 50:
				reg |= I365_VPP1_5V;
				break;
			case 120:
				reg |= I365_VPP1_12V;
				break;
			}
		} else {
			/* i82365SL-B style */
			switch (state->Vcc) {
			case 50:
				reg |= I365_VCC_5V;
				break;
			default:
				reg = 0;
				break;
			}
			switch (state->Vpp) {
			case 50:
				reg |= I365_VPP1_5V | I365_VPP2_5V;
				break;
			case 120:
				reg |= I365_VPP1_12V | I365_VPP2_12V;
				break;
			}
		}

		if (reg != old)
			exca_writeb(socket, I365_POWER, reg);
	} else {
		u32 reg = 0;	/* CB_SC_STPCLK? */
		switch (state->Vcc) {
		case 33:
			reg = CB_SC_VCC_3V;
			break;
		case 50:
			reg = CB_SC_VCC_5V;
			break;
		default:
			reg = 0;
			break;
		}
		switch (state->Vpp) {
		case 33:
			reg |= CB_SC_VPP_3V;
			break;
		case 50:
			reg |= CB_SC_VPP_5V;
			break;
		case 120:
			reg |= CB_SC_VPP_12V;
			break;
		}
		if (reg != cb_readl(socket, CB_SOCKET_CONTROL))
			cb_writel(socket, CB_SOCKET_CONTROL, reg);
	}
}