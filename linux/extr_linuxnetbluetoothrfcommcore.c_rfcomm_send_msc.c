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
struct rfcomm_session {int initiator; } ;
struct rfcomm_msc {int v24_sig; void* dlci; } ;
struct rfcomm_mcc {void* len; int /*<<< orphan*/  type; } ;
struct rfcomm_hdr {void* len; int /*<<< orphan*/  ctrl; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int,int) ; 
 int /*<<< orphan*/  RFCOMM_MSC ; 
 int /*<<< orphan*/  RFCOMM_UIH ; 
 void* __addr (int,int) ; 
 int /*<<< orphan*/  __ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __fcs (int*) ; 
 void* __len8 (int) ; 
 int /*<<< orphan*/  __mcc_type (int,int /*<<< orphan*/ ) ; 
 int rfcomm_send_frame (struct rfcomm_session*,int*,int) ; 

__attribute__((used)) static int rfcomm_send_msc(struct rfcomm_session *s, int cr, u8 dlci, u8 v24_sig)
{
	struct rfcomm_hdr *hdr;
	struct rfcomm_mcc *mcc;
	struct rfcomm_msc *msc;
	u8 buf[16], *ptr = buf;

	BT_DBG("%p cr %d v24 0x%x", s, cr, v24_sig);

	hdr = (void *) ptr; ptr += sizeof(*hdr);
	hdr->addr = __addr(s->initiator, 0);
	hdr->ctrl = __ctrl(RFCOMM_UIH, 0);
	hdr->len  = __len8(sizeof(*mcc) + sizeof(*msc));

	mcc = (void *) ptr; ptr += sizeof(*mcc);
	mcc->type = __mcc_type(cr, RFCOMM_MSC);
	mcc->len  = __len8(sizeof(*msc));

	msc = (void *) ptr; ptr += sizeof(*msc);
	msc->dlci    = __addr(1, dlci);
	msc->v24_sig = v24_sig | 0x01;

	*ptr = __fcs(buf); ptr++;

	return rfcomm_send_frame(s, buf, ptr - buf);
}