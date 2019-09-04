#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bnx2i_conn {TYPE_3__* ep; } ;
struct TYPE_4__ {int header; } ;
struct bnx2i_5771x_dbell {TYPE_1__ dbell; } ;
typedef  int /*<<< orphan*/  dbell ;
struct TYPE_5__ {int /*<<< orphan*/  ctx_base; } ;
struct TYPE_6__ {TYPE_2__ qp; } ;

/* Variables and functions */
 int B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT ; 
 int B577XX_ISCSI_CONNECTION_TYPE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bnx2i_5771x_dbell*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2i_ring_577xx_doorbell(struct bnx2i_conn *conn)
{
	struct bnx2i_5771x_dbell dbell;
	u32 msg;

	memset(&dbell, 0, sizeof(dbell));
	dbell.dbell.header = (B577XX_ISCSI_CONNECTION_TYPE <<
			      B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT);
	msg = *((u32 *)&dbell);
	/* TODO : get doorbell register mapping */
	writel(cpu_to_le32(msg), conn->ep->qp.ctx_base);
}