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
struct sctp_transport {int /*<<< orphan*/  hb_nonce; int /*<<< orphan*/  ipaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct sctp_sender_hb_info {int /*<<< orphan*/  hb_nonce; int /*<<< orphan*/  sent_at; int /*<<< orphan*/  daddr; TYPE_1__ param_hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  hbs_hdr; } ;
struct sctp_chunk {TYPE_2__ subh; struct sctp_transport* transport; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  hbinfo ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_CID_HEARTBEAT ; 
 int /*<<< orphan*/  SCTP_PARAM_HEARTBEAT_INFO ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_sender_hb_info*) ; 
 struct sctp_chunk* sctp_make_control (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct sctp_chunk *sctp_make_heartbeat(const struct sctp_association *asoc,
				       const struct sctp_transport *transport)
{
	struct sctp_sender_hb_info hbinfo;
	struct sctp_chunk *retval;

	retval = sctp_make_control(asoc, SCTP_CID_HEARTBEAT, 0,
				   sizeof(hbinfo), GFP_ATOMIC);

	if (!retval)
		goto nodata;

	hbinfo.param_hdr.type = SCTP_PARAM_HEARTBEAT_INFO;
	hbinfo.param_hdr.length = htons(sizeof(hbinfo));
	hbinfo.daddr = transport->ipaddr;
	hbinfo.sent_at = jiffies;
	hbinfo.hb_nonce = transport->hb_nonce;

	/* Cast away the 'const', as this is just telling the chunk
	 * what transport it belongs to.
	 */
	retval->transport = (struct sctp_transport *) transport;
	retval->subh.hbs_hdr = sctp_addto_chunk(retval, sizeof(hbinfo),
						&hbinfo);

nodata:
	return retval;
}