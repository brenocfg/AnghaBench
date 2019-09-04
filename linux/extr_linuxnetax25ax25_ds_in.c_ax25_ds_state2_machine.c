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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_COMMAND ; 
#define  AX25_DISC 136 
#define  AX25_DM 135 
#define  AX25_I 134 
 int AX25_POLLON ; 
#define  AX25_REJ 133 
 int /*<<< orphan*/  AX25_RESPONSE ; 
#define  AX25_RNR 132 
#define  AX25_RR 131 
#define  AX25_SABM 130 
#define  AX25_SABME 129 
#define  AX25_UA 128 
 int /*<<< orphan*/  ax25_dama_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ax25_disconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_send_control (int /*<<< orphan*/ *,int const,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ax25_ds_state2_machine(ax25_cb *ax25, struct sk_buff *skb, int frametype, int pf, int type)
{
	switch (frametype) {
	case AX25_SABM:
	case AX25_SABME:
		ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
		ax25_dama_off(ax25);
		break;

	case AX25_DISC:
		ax25_send_control(ax25, AX25_UA, pf, AX25_RESPONSE);
		ax25_dama_off(ax25);
		ax25_disconnect(ax25, 0);
		break;

	case AX25_DM:
	case AX25_UA:
		if (pf) {
			ax25_dama_off(ax25);
			ax25_disconnect(ax25, 0);
		}
		break;

	case AX25_I:
	case AX25_REJ:
	case AX25_RNR:
	case AX25_RR:
		if (pf) {
			ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
			ax25_dama_off(ax25);
		}
		break;

	default:
		break;
	}

	return 0;
}