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
struct fwtty_peer {int dummy; } ;
struct fwserial_mgmt_pkt {int dummy; } ;
struct fw_request {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int RCODE_CONFLICT_ERROR ; 
 int RCODE_TYPE_ERROR ; 
#define  TCODE_WRITE_BLOCK_REQUEST 128 
 int /*<<< orphan*/  __dump_peer_list (struct fw_card*) ; 
 struct fwtty_peer* __fwserial_peer_by_node_id (struct fw_card*,int,int) ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int) ; 
 int fwserial_parse_mgmt_write (struct fwtty_peer*,struct fwserial_mgmt_pkt*,unsigned long long,size_t) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fw_card*,char*,int,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void fwserial_mgmt_handler(struct fw_card *card,
				  struct fw_request *request,
				  int tcode, int destination, int source,
				  int generation,
				  unsigned long long addr,
				  void *data, size_t len,
				  void *callback_data)
{
	struct fwserial_mgmt_pkt *pkt = data;
	struct fwtty_peer *peer;
	int rcode;

	rcu_read_lock();
	peer = __fwserial_peer_by_node_id(card, generation, source);
	if (!peer) {
		fwtty_dbg(card, "peer(%d:%x) not found\n", generation, source);
		__dump_peer_list(card);
		rcode = RCODE_CONFLICT_ERROR;

	} else {
		switch (tcode) {
		case TCODE_WRITE_BLOCK_REQUEST:
			rcode = fwserial_parse_mgmt_write(peer, pkt, addr, len);
			break;

		default:
			rcode = RCODE_TYPE_ERROR;
		}
	}

	rcu_read_unlock();
	fw_send_response(card, request, rcode);
}