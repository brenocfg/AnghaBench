#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_21__ {int modulus; int condition; int vr; void* state; int /*<<< orphan*/  va; int /*<<< orphan*/  vs; TYPE_1__* ax25_dev; int /*<<< orphan*/  window; } ;
typedef  TYPE_2__ ax25_cb ;
struct TYPE_20__ {int /*<<< orphan*/ * values; } ;

/* Variables and functions */
 int AX25_COMMAND ; 
 int AX25_COND_ACK_PENDING ; 
 int AX25_COND_OWN_RX_BUSY ; 
 int AX25_COND_PEER_RX_BUSY ; 
 int AX25_COND_REJECT ; 
#define  AX25_DISC 137 
#define  AX25_DM 136 
 int AX25_EMODULUS ; 
#define  AX25_FRMR 135 
#define  AX25_I 134 
#define  AX25_ILLEGAL 133 
 int AX25_MODULUS ; 
#define  AX25_REJ 132 
 int /*<<< orphan*/  AX25_RESPONSE ; 
#define  AX25_RNR 131 
#define  AX25_RR 130 
#define  AX25_SABM 129 
#define  AX25_SABME 128 
 void* AX25_STATE_1 ; 
 int const AX25_UA ; 
 size_t AX25_VALUES_EWINDOW ; 
 size_t AX25_VALUES_WINDOW ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  ax25_calculate_rtt (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_check_iframes_acked (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ax25_disconnect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_frames_acked (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ax25_requeue_frames (TYPE_2__*) ; 
 int ax25_rx_iframe (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  ax25_send_control (TYPE_2__*,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_start_idletimer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_start_t2timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_start_t3timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_std_enquiry_response (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_std_establish_data_link (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_std_nr_error_recovery (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_stop_t1timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_stop_t2timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_validate_nr (TYPE_2__*,int) ; 

__attribute__((used)) static int ax25_std_state3_machine(ax25_cb *ax25, struct sk_buff *skb, int frametype, int ns, int nr, int pf, int type)
{
	int queued = 0;

	switch (frametype) {
	case AX25_SABM:
	case AX25_SABME:
		if (frametype == AX25_SABM) {
			ax25->modulus = AX25_MODULUS;
			ax25->window  = ax25->ax25_dev->values[AX25_VALUES_WINDOW];
		} else {
			ax25->modulus = AX25_EMODULUS;
			ax25->window  = ax25->ax25_dev->values[AX25_VALUES_EWINDOW];
		}
		ax25_send_control(ax25, AX25_UA, pf, AX25_RESPONSE);
		ax25_stop_t1timer(ax25);
		ax25_stop_t2timer(ax25);
		ax25_start_t3timer(ax25);
		ax25_start_idletimer(ax25);
		ax25->condition = 0x00;
		ax25->vs        = 0;
		ax25->va        = 0;
		ax25->vr        = 0;
		ax25_requeue_frames(ax25);
		break;

	case AX25_DISC:
		ax25_send_control(ax25, AX25_UA, pf, AX25_RESPONSE);
		ax25_disconnect(ax25, 0);
		break;

	case AX25_DM:
		ax25_disconnect(ax25, ECONNRESET);
		break;

	case AX25_RR:
	case AX25_RNR:
		if (frametype == AX25_RR)
			ax25->condition &= ~AX25_COND_PEER_RX_BUSY;
		else
			ax25->condition |= AX25_COND_PEER_RX_BUSY;
		if (type == AX25_COMMAND && pf)
			ax25_std_enquiry_response(ax25);
		if (ax25_validate_nr(ax25, nr)) {
			ax25_check_iframes_acked(ax25, nr);
		} else {
			ax25_std_nr_error_recovery(ax25);
			ax25->state = AX25_STATE_1;
		}
		break;

	case AX25_REJ:
		ax25->condition &= ~AX25_COND_PEER_RX_BUSY;
		if (type == AX25_COMMAND && pf)
			ax25_std_enquiry_response(ax25);
		if (ax25_validate_nr(ax25, nr)) {
			ax25_frames_acked(ax25, nr);
			ax25_calculate_rtt(ax25);
			ax25_stop_t1timer(ax25);
			ax25_start_t3timer(ax25);
			ax25_requeue_frames(ax25);
		} else {
			ax25_std_nr_error_recovery(ax25);
			ax25->state = AX25_STATE_1;
		}
		break;

	case AX25_I:
		if (!ax25_validate_nr(ax25, nr)) {
			ax25_std_nr_error_recovery(ax25);
			ax25->state = AX25_STATE_1;
			break;
		}
		if (ax25->condition & AX25_COND_PEER_RX_BUSY) {
			ax25_frames_acked(ax25, nr);
		} else {
			ax25_check_iframes_acked(ax25, nr);
		}
		if (ax25->condition & AX25_COND_OWN_RX_BUSY) {
			if (pf) ax25_std_enquiry_response(ax25);
			break;
		}
		if (ns == ax25->vr) {
			ax25->vr = (ax25->vr + 1) % ax25->modulus;
			queued = ax25_rx_iframe(ax25, skb);
			if (ax25->condition & AX25_COND_OWN_RX_BUSY)
				ax25->vr = ns;	/* ax25->vr - 1 */
			ax25->condition &= ~AX25_COND_REJECT;
			if (pf) {
				ax25_std_enquiry_response(ax25);
			} else {
				if (!(ax25->condition & AX25_COND_ACK_PENDING)) {
					ax25->condition |= AX25_COND_ACK_PENDING;
					ax25_start_t2timer(ax25);
				}
			}
		} else {
			if (ax25->condition & AX25_COND_REJECT) {
				if (pf) ax25_std_enquiry_response(ax25);
			} else {
				ax25->condition |= AX25_COND_REJECT;
				ax25_send_control(ax25, AX25_REJ, pf, AX25_RESPONSE);
				ax25->condition &= ~AX25_COND_ACK_PENDING;
			}
		}
		break;

	case AX25_FRMR:
	case AX25_ILLEGAL:
		ax25_std_establish_data_link(ax25);
		ax25->state = AX25_STATE_1;
		break;

	default:
		break;
	}

	return queued;
}