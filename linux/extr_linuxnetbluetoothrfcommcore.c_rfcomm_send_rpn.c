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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rfcomm_session {int initiator; } ;
struct rfcomm_rpn {int /*<<< orphan*/  param_mask; void* xoff_char; void* xon_char; void* flow_ctrl; int /*<<< orphan*/  line_settings; void* bit_rate; void* dlci; } ;
struct rfcomm_mcc {void* len; int /*<<< orphan*/  type; } ;
struct rfcomm_hdr {void* len; int /*<<< orphan*/  ctrl; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int,void*,void*,void*,void*,void*,void*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFCOMM_RPN ; 
 int /*<<< orphan*/  RFCOMM_UIH ; 
 void* __addr (int,void*) ; 
 int /*<<< orphan*/  __ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* __fcs (void**) ; 
 void* __len8 (int) ; 
 int /*<<< orphan*/  __mcc_type (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rpn_line_settings (void*,void*,void*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int rfcomm_send_frame (struct rfcomm_session*,void**,int) ; 

int rfcomm_send_rpn(struct rfcomm_session *s, int cr, u8 dlci,
			u8 bit_rate, u8 data_bits, u8 stop_bits,
			u8 parity, u8 flow_ctrl_settings,
			u8 xon_char, u8 xoff_char, u16 param_mask)
{
	struct rfcomm_hdr *hdr;
	struct rfcomm_mcc *mcc;
	struct rfcomm_rpn *rpn;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d dlci %d bit_r 0x%x data_b 0x%x stop_b 0x%x parity 0x%x"
			" flwc_s 0x%x xon_c 0x%x xoff_c 0x%x p_mask 0x%x",
		s, cr, dlci, bit_rate, data_bits, stop_bits, parity,
		flow_ctrl_settings, xon_char, xoff_char, param_mask);

	hdr = (void *) ptr; ptr += sizeof(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(sizeof(*mcc) + sizeof(*rpn));

	mcc = (void *) ptr; ptr += sizeof(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_RPN);
	mcc->len  = __len8(sizeof(*rpn));

	rpn = (void *) ptr; ptr += sizeof(*rpn);
	rpn->dlci          = __addr(1, dlci);
	rpn->bit_rate      = bit_rate;
	rpn->line_settings = __rpn_line_settings(data_bits, stop_bits, parity);
	rpn->flow_ctrl     = flow_ctrl_settings;
	rpn->xon_char      = xon_char;
	rpn->xoff_char     = xoff_char;
	rpn->param_mask    = cpu_to_le16(param_mask);

	*ptr = __fcs(buf); ptr++;

	return rfcomm_send_frame(s, buf, ptr - buf);
}