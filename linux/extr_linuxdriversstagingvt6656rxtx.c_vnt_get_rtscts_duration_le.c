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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_usb_send_context {int frame_len; int need_ack; struct vnt_private* priv; } ;
struct vnt_private {int sifs; int /*<<< orphan*/  top_ofdm_basic_rate; int /*<<< orphan*/  preamble_type; int /*<<< orphan*/  top_cck_basic_rate; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
#define  CTSDUR_BA 137 
#define  CTSDUR_BA_F0 136 
#define  CTSDUR_BA_F1 135 
#define  RTSDUR_AA 134 
#define  RTSDUR_AA_F0 133 
#define  RTSDUR_AA_F1 132 
#define  RTSDUR_BA 131 
#define  RTSDUR_BA_F0 130 
#define  RTSDUR_BA_F1 129 
#define  RTSDUR_BB 128 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int vnt_get_frame_time (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int vnt_get_rsvtime (struct vnt_private*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __le16 vnt_get_rtscts_duration_le(struct vnt_usb_send_context *context,
					 u8 dur_type, u8 pkt_type, u16 rate)
{
	struct vnt_private *priv = context->priv;
	u32 cts_time = 0, dur_time = 0;
	u32 frame_length = context->frame_len;
	u8 need_ack = context->need_ack;

	switch (dur_type) {
	case RTSDUR_BB:
	case RTSDUR_BA:
	case RTSDUR_BA_F0:
	case RTSDUR_BA_F1:
		cts_time = vnt_get_frame_time(priv->preamble_type, pkt_type,
					      14, priv->top_cck_basic_rate);
		dur_time = cts_time + 2 * priv->sifs +
			vnt_get_rsvtime(priv, pkt_type,
					frame_length, rate, need_ack);
		break;

	case RTSDUR_AA:
	case RTSDUR_AA_F0:
	case RTSDUR_AA_F1:
		cts_time = vnt_get_frame_time(priv->preamble_type, pkt_type,
					      14, priv->top_ofdm_basic_rate);
		dur_time = cts_time + 2 * priv->sifs +
			vnt_get_rsvtime(priv, pkt_type,
					frame_length, rate, need_ack);
		break;

	case CTSDUR_BA:
	case CTSDUR_BA_F0:
	case CTSDUR_BA_F1:
		dur_time = priv->sifs + vnt_get_rsvtime(priv,
				pkt_type, frame_length, rate, need_ack);
		break;

	default:
		break;
	}

	return cpu_to_le16((u16)dur_time);
}