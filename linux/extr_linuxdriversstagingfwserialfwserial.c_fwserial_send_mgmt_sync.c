#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fwtty_peer {int generation; int /*<<< orphan*/  unit; int /*<<< orphan*/  mgmt_addr; int /*<<< orphan*/  speed; int /*<<< orphan*/  node_id; TYPE_2__* serial; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct fwserial_mgmt_pkt {TYPE_1__ hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int RCODE_BUSY ; 
 int RCODE_GENERATION ; 
 int RCODE_SEND_ERROR ; 
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int fw_run_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fwserial_mgmt_pkt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwtty_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static inline int fwserial_send_mgmt_sync(struct fwtty_peer *peer,
					  struct fwserial_mgmt_pkt *pkt)
{
	int generation;
	int rcode, tries = 5;

	do {
		generation = peer->generation;
		smp_rmb();

		rcode = fw_run_transaction(peer->serial->card,
					   TCODE_WRITE_BLOCK_REQUEST,
					   peer->node_id,
					   generation, peer->speed,
					   peer->mgmt_addr,
					   pkt, be16_to_cpu(pkt->hdr.len));
		if (rcode == RCODE_BUSY || rcode == RCODE_SEND_ERROR ||
		    rcode == RCODE_GENERATION) {
			fwtty_dbg(&peer->unit, "mgmt write error: %d\n", rcode);
			continue;
		} else {
			break;
		}
	} while (--tries > 0);
	return rcode;
}