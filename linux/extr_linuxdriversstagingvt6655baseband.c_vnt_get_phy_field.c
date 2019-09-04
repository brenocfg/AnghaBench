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
typedef  int u16 ;
struct vnt_private {int byPreambleType; } ;
struct vnt_phy_field {int signal; int service; void* len; } ;

/* Variables and functions */
 int PK_TYPE_11A ; 
 int PK_TYPE_11B ; 
#define  RATE_11M 139 
#define  RATE_12M 138 
#define  RATE_18M 137 
#define  RATE_1M 136 
#define  RATE_24M 135 
#define  RATE_2M 134 
#define  RATE_36M 133 
#define  RATE_48M 132 
#define  RATE_54M 131 
#define  RATE_5M 130 
#define  RATE_6M 129 
#define  RATE_9M 128 
 void* cpu_to_le16 (int) ; 

void vnt_get_phy_field(struct vnt_private *priv, u32 frame_length,
		       u16 tx_rate, u8 pkt_type, struct vnt_phy_field *phy)
{
	u32 bit_count;
	u32 count = 0;
	u32 tmp;
	int ext_bit;
	u8 preamble_type = priv->byPreambleType;

	bit_count = frame_length * 8;
	ext_bit = false;

	switch (tx_rate) {
	case RATE_1M:
		count = bit_count;

		phy->signal = 0x00;

		break;
	case RATE_2M:
		count = bit_count / 2;

		if (preamble_type == 1)
			phy->signal = 0x09;
		else
			phy->signal = 0x01;

		break;
	case RATE_5M:
		count = (bit_count * 10) / 55;
		tmp = (count * 55) / 10;

		if (tmp != bit_count)
			count++;

		if (preamble_type == 1)
			phy->signal = 0x0a;
		else
			phy->signal = 0x02;

		break;
	case RATE_11M:
		count = bit_count / 11;
		tmp = count * 11;

		if (tmp != bit_count) {
			count++;

			if ((bit_count - tmp) <= 3)
				ext_bit = true;
		}

		if (preamble_type == 1)
			phy->signal = 0x0b;
		else
			phy->signal = 0x03;

		break;
	case RATE_6M:
		if (pkt_type == PK_TYPE_11A)
			phy->signal = 0x9b;
		else
			phy->signal = 0x8b;

		break;
	case RATE_9M:
		if (pkt_type == PK_TYPE_11A)
			phy->signal = 0x9f;
		else
			phy->signal = 0x8f;

		break;
	case RATE_12M:
		if (pkt_type == PK_TYPE_11A)
			phy->signal = 0x9a;
		else
			phy->signal = 0x8a;

		break;
	case RATE_18M:
		if (pkt_type == PK_TYPE_11A)
			phy->signal = 0x9e;
		else
			phy->signal = 0x8e;

		break;
	case RATE_24M:
		if (pkt_type == PK_TYPE_11A)
			phy->signal = 0x99;
		else
			phy->signal = 0x89;

		break;
	case RATE_36M:
		if (pkt_type == PK_TYPE_11A)
			phy->signal = 0x9d;
		else
			phy->signal = 0x8d;

		break;
	case RATE_48M:
		if (pkt_type == PK_TYPE_11A)
			phy->signal = 0x98;
		else
			phy->signal = 0x88;

		break;
	case RATE_54M:
		if (pkt_type == PK_TYPE_11A)
			phy->signal = 0x9c;
		else
			phy->signal = 0x8c;
		break;
	default:
		if (pkt_type == PK_TYPE_11A)
			phy->signal = 0x9c;
		else
			phy->signal = 0x8c;
		break;
	}

	if (pkt_type == PK_TYPE_11B) {
		phy->service = 0x00;
		if (ext_bit)
			phy->service |= 0x80;
		phy->len = cpu_to_le16((u16)count);
	} else {
		phy->service = 0x00;
		phy->len = cpu_to_le16((u16)frame_length);
	}
}