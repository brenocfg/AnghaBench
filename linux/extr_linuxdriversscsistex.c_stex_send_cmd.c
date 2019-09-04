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
typedef  size_t u16 ;
struct st_hba {scalar_t__ mmio_base; int /*<<< orphan*/  req_head; int /*<<< orphan*/  out_req_cnt; TYPE_1__* ccb; } ;
struct req_msg {int /*<<< orphan*/  tag; } ;
struct TYPE_2__ {struct req_msg* req; } ;

/* Variables and functions */
 scalar_t__ IDBL ; 
 scalar_t__ IMR0 ; 
 int /*<<< orphan*/  MU_INBOUND_DOORBELL_REQHEADCHANGED ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
stex_send_cmd(struct st_hba *hba, struct req_msg *req, u16 tag)
{
	req->tag = cpu_to_le16(tag);

	hba->ccb[tag].req = req;
	hba->out_req_cnt++;

	writel(hba->req_head, hba->mmio_base + IMR0);
	writel(MU_INBOUND_DOORBELL_REQHEADCHANGED, hba->mmio_base + IDBL);
	readl(hba->mmio_base + IDBL); /* flush */
}