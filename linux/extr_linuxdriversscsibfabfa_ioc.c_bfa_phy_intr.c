#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bfi_phy_write_rsp_s {int /*<<< orphan*/  status; } ;
struct bfi_phy_stats_rsp_s {int /*<<< orphan*/  status; } ;
struct bfi_phy_read_rsp_s {int /*<<< orphan*/  length; int /*<<< orphan*/  status; } ;
struct bfi_phy_query_rsp_s {int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int msg_id; } ;
struct bfi_mbmsg_s {TYPE_1__ mh; } ;
struct bfa_phy_stats_s {int status; } ;
struct bfa_phy_s {int ubuf; int status; int residue; int offset; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  op_busy; scalar_t__ dbuf_kva; } ;
struct bfa_phy_attr_s {int status; int length; } ;

/* Variables and functions */
 int BFA_STATUS_OK ; 
#define  BFI_PHY_I2H_QUERY_RSP 131 
#define  BFI_PHY_I2H_READ_RSP 130 
#define  BFI_PHY_I2H_STATS_RSP 129 
#define  BFI_PHY_I2H_WRITE_RSP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_phy_ntoh32 (int*,int*,int) ; 
 int /*<<< orphan*/  bfa_phy_read_send (struct bfa_phy_s*) ; 
 int /*<<< orphan*/  bfa_phy_write_send (struct bfa_phy_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_phy_s*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int) ; 

void
bfa_phy_intr(void *phyarg, struct bfi_mbmsg_s *msg)
{
	struct bfa_phy_s *phy = phyarg;
	u32	status;

	union {
		struct bfi_phy_query_rsp_s *query;
		struct bfi_phy_stats_rsp_s *stats;
		struct bfi_phy_write_rsp_s *write;
		struct bfi_phy_read_rsp_s *read;
		struct bfi_mbmsg_s   *msg;
	} m;

	m.msg = msg;
	bfa_trc(phy, msg->mh.msg_id);

	if (!phy->op_busy) {
		/* receiving response after ioc failure */
		bfa_trc(phy, 0x9999);
		return;
	}

	switch (msg->mh.msg_id) {
	case BFI_PHY_I2H_QUERY_RSP:
		status = be32_to_cpu(m.query->status);
		bfa_trc(phy, status);

		if (status == BFA_STATUS_OK) {
			struct bfa_phy_attr_s *attr =
				(struct bfa_phy_attr_s *) phy->ubuf;
			bfa_phy_ntoh32((u32 *)attr, (u32 *)phy->dbuf_kva,
					sizeof(struct bfa_phy_attr_s));
			bfa_trc(phy, attr->status);
			bfa_trc(phy, attr->length);
		}

		phy->status = status;
		phy->op_busy = 0;
		if (phy->cbfn)
			phy->cbfn(phy->cbarg, phy->status);
		break;
	case BFI_PHY_I2H_STATS_RSP:
		status = be32_to_cpu(m.stats->status);
		bfa_trc(phy, status);

		if (status == BFA_STATUS_OK) {
			struct bfa_phy_stats_s *stats =
				(struct bfa_phy_stats_s *) phy->ubuf;
			bfa_phy_ntoh32((u32 *)stats, (u32 *)phy->dbuf_kva,
				sizeof(struct bfa_phy_stats_s));
				bfa_trc(phy, stats->status);
		}

		phy->status = status;
		phy->op_busy = 0;
		if (phy->cbfn)
			phy->cbfn(phy->cbarg, phy->status);
		break;
	case BFI_PHY_I2H_WRITE_RSP:
		status = be32_to_cpu(m.write->status);
		bfa_trc(phy, status);

		if (status != BFA_STATUS_OK || phy->residue == 0) {
			phy->status = status;
			phy->op_busy = 0;
			if (phy->cbfn)
				phy->cbfn(phy->cbarg, phy->status);
		} else {
			bfa_trc(phy, phy->offset);
			bfa_phy_write_send(phy);
		}
		break;
	case BFI_PHY_I2H_READ_RSP:
		status = be32_to_cpu(m.read->status);
		bfa_trc(phy, status);

		if (status != BFA_STATUS_OK) {
			phy->status = status;
			phy->op_busy = 0;
			if (phy->cbfn)
				phy->cbfn(phy->cbarg, phy->status);
		} else {
			u32 len = be32_to_cpu(m.read->length);
			u16 *buf = (u16 *)(phy->ubuf + phy->offset);
			u16 *dbuf = (u16 *)phy->dbuf_kva;
			int i, sz = len >> 1;

			bfa_trc(phy, phy->offset);
			bfa_trc(phy, len);

			for (i = 0; i < sz; i++)
				buf[i] = be16_to_cpu(dbuf[i]);

			phy->residue -= len;
			phy->offset += len;

			if (phy->residue == 0) {
				phy->status = status;
				phy->op_busy = 0;
				if (phy->cbfn)
					phy->cbfn(phy->cbarg, phy->status);
			} else
				bfa_phy_read_send(phy);
		}
		break;
	default:
		WARN_ON(1);
	}
}