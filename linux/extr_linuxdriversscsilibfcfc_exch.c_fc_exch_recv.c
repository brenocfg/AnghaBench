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
typedef  int u32 ;
struct fc_lport {scalar_t__ state; } ;
struct fc_frame_header {int /*<<< orphan*/  fh_type; int /*<<< orphan*/  fh_rx_id; int /*<<< orphan*/  fh_ox_id; int /*<<< orphan*/  fh_f_ctl; } ;
struct fc_frame {int dummy; } ;
struct fc_exch_mgr_anchor {int /*<<< orphan*/  mp; } ;

/* Variables and functions */
#define  FC_EOF_N 129 
#define  FC_EOF_T 128 
 int FC_FC_END_SEQ ; 
 int FC_FC_EX_CTX ; 
 scalar_t__ FC_FC_FILL (int) ; 
 int FC_FC_SEQ_CTX ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,...) ; 
 int /*<<< orphan*/  FC_TYPE_BLS ; 
 scalar_t__ LPORT_ST_DISABLED ; 
 int /*<<< orphan*/  fc_exch_recv_bls (int /*<<< orphan*/ ,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_exch_recv_req (struct fc_lport*,int /*<<< orphan*/ ,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_exch_recv_resp (int /*<<< orphan*/ ,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_exch_recv_seq_resp (int /*<<< orphan*/ ,struct fc_frame*) ; 
 struct fc_exch_mgr_anchor* fc_find_ema (int,struct fc_lport*,struct fc_frame_header*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 int /*<<< orphan*/  fp_skb (struct fc_frame*) ; 
 int fr_eof (struct fc_frame*) ; 
 scalar_t__ fr_len (struct fc_frame*) ; 
 int ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (int /*<<< orphan*/ ,scalar_t__) ; 

void fc_exch_recv(struct fc_lport *lport, struct fc_frame *fp)
{
	struct fc_frame_header *fh = fc_frame_header_get(fp);
	struct fc_exch_mgr_anchor *ema;
	u32 f_ctl;

	/* lport lock ? */
	if (!lport || lport->state == LPORT_ST_DISABLED) {
		FC_LPORT_DBG(lport, "Receiving frames for an lport that "
			     "has not been initialized correctly\n");
		fc_frame_free(fp);
		return;
	}

	f_ctl = ntoh24(fh->fh_f_ctl);
	ema = fc_find_ema(f_ctl, lport, fh);
	if (!ema) {
		FC_LPORT_DBG(lport, "Unable to find Exchange Manager Anchor,"
				    "fc_ctl <0x%x>, xid <0x%x>\n",
				     f_ctl,
				     (f_ctl & FC_FC_EX_CTX) ?
				     ntohs(fh->fh_ox_id) :
				     ntohs(fh->fh_rx_id));
		fc_frame_free(fp);
		return;
	}

	/*
	 * If frame is marked invalid, just drop it.
	 */
	switch (fr_eof(fp)) {
	case FC_EOF_T:
		if (f_ctl & FC_FC_END_SEQ)
			skb_trim(fp_skb(fp), fr_len(fp) - FC_FC_FILL(f_ctl));
		/* fall through */
	case FC_EOF_N:
		if (fh->fh_type == FC_TYPE_BLS)
			fc_exch_recv_bls(ema->mp, fp);
		else if ((f_ctl & (FC_FC_EX_CTX | FC_FC_SEQ_CTX)) ==
			 FC_FC_EX_CTX)
			fc_exch_recv_seq_resp(ema->mp, fp);
		else if (f_ctl & FC_FC_SEQ_CTX)
			fc_exch_recv_resp(ema->mp, fp);
		else	/* no EX_CTX and no SEQ_CTX */
			fc_exch_recv_req(lport, ema->mp, fp);
		break;
	default:
		FC_LPORT_DBG(lport, "dropping invalid frame (eof %x)",
			     fr_eof(fp));
		fc_frame_free(fp);
	}
}