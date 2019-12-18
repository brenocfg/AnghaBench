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
struct TYPE_4__ {scalar_t__ revision; int /*<<< orphan*/  length; } ;
struct ncsi_rsp_pkt_hdr {int /*<<< orphan*/  reason; int /*<<< orphan*/  code; TYPE_1__ common; } ;
struct ncsi_request {TYPE_3__* ndp; int /*<<< orphan*/  rsp; } ;
typedef  unsigned short __be32 ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_2__ ndev; } ;

/* Variables and functions */
 int ALIGN (unsigned short,int) ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ NCSI_PKT_REVISION ; 
 unsigned short NCSI_PKT_RSP_C_COMPLETED ; 
 unsigned short NCSI_PKT_RSP_R_NO_ERROR ; 
 unsigned short htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncsi_calculate_checksum (unsigned char*,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ntohl (unsigned short) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_validate_rsp_pkt(struct ncsi_request *nr,
				 unsigned short payload)
{
	struct ncsi_rsp_pkt_hdr *h;
	u32 checksum;
	__be32 *pchecksum;

	/* Check NCSI packet header. We don't need validate
	 * the packet type, which should have been checked
	 * before calling this function.
	 */
	h = (struct ncsi_rsp_pkt_hdr *)skb_network_header(nr->rsp);

	if (h->common.revision != NCSI_PKT_REVISION) {
		netdev_dbg(nr->ndp->ndev.dev,
			   "NCSI: unsupported header revision\n");
		return -EINVAL;
	}
	if (ntohs(h->common.length) != payload) {
		netdev_dbg(nr->ndp->ndev.dev,
			   "NCSI: payload length mismatched\n");
		return -EINVAL;
	}

	/* Check on code and reason */
	if (ntohs(h->code) != NCSI_PKT_RSP_C_COMPLETED ||
	    ntohs(h->reason) != NCSI_PKT_RSP_R_NO_ERROR) {
		netdev_dbg(nr->ndp->ndev.dev,
			   "NCSI: non zero response/reason code %04xh, %04xh\n",
			    ntohs(h->code), ntohs(h->reason));
		return -EPERM;
	}

	/* Validate checksum, which might be zeroes if the
	 * sender doesn't support checksum according to NCSI
	 * specification.
	 */
	pchecksum = (__be32 *)((void *)(h + 1) + ALIGN(payload, 4) - 4);
	if (ntohl(*pchecksum) == 0)
		return 0;

	checksum = ncsi_calculate_checksum((unsigned char *)h,
					   sizeof(*h) + payload - 4);

	if (*pchecksum != htonl(checksum)) {
		netdev_dbg(nr->ndp->ndev.dev,
			   "NCSI: checksum mismatched; recd: %08x calc: %08x\n",
			   *pchecksum, htonl(checksum));
		return -EINVAL;
	}

	return 0;
}