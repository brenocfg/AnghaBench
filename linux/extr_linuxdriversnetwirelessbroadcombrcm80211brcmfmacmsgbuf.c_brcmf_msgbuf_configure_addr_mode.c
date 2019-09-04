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
struct brcmf_pub {TYPE_1__* proto; } ;
struct brcmf_msgbuf {int /*<<< orphan*/  flow; } ;
typedef  enum proto_addr_mode { ____Placeholder_proto_addr_mode } proto_addr_mode ;
struct TYPE_2__ {scalar_t__ pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_flowring_configure_addr_mode (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
brcmf_msgbuf_configure_addr_mode(struct brcmf_pub *drvr, int ifidx,
				 enum proto_addr_mode addr_mode)
{
	struct brcmf_msgbuf *msgbuf = (struct brcmf_msgbuf *)drvr->proto->pd;

	brcmf_flowring_configure_addr_mode(msgbuf->flow, ifidx, addr_mode);
}