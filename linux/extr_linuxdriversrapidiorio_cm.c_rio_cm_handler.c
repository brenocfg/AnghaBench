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
struct rio_ch_chan_hdr {int ch_op; int /*<<< orphan*/  src_ch; int /*<<< orphan*/  dst_ch; } ;
struct cm_dev {int /*<<< orphan*/  mport; } ;

/* Variables and functions */
#define  CM_CONN_ACK 130 
#define  CM_CONN_CLOSE 129 
#define  CM_CONN_REQ 128 
 int /*<<< orphan*/  RX_CMD ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rio_mport_is_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_close_handler (void*) ; 
 int /*<<< orphan*/  riocm_debug (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_error (char*) ; 
 int /*<<< orphan*/  riocm_req_handler (struct cm_dev*,void*) ; 
 int /*<<< orphan*/  riocm_resp_handler (void*) ; 

__attribute__((used)) static void rio_cm_handler(struct cm_dev *cm, void *data)
{
	struct rio_ch_chan_hdr *hdr;

	if (!rio_mport_is_running(cm->mport))
		goto out;

	hdr = data;

	riocm_debug(RX_CMD, "OP=%x for ch=%d from %d",
		    hdr->ch_op, ntohs(hdr->dst_ch), ntohs(hdr->src_ch));

	switch (hdr->ch_op) {
	case CM_CONN_REQ:
		riocm_req_handler(cm, data);
		break;
	case CM_CONN_ACK:
		riocm_resp_handler(data);
		break;
	case CM_CONN_CLOSE:
		riocm_close_handler(data);
		break;
	default:
		riocm_error("Invalid packet header");
		break;
	}
out:
	kfree(data);
}