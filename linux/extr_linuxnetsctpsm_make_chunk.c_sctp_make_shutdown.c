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
struct sctp_shutdownhdr {int /*<<< orphan*/  cum_tsn_ack; } ;
struct TYPE_3__ {int /*<<< orphan*/  shutdown_hdr; } ;
struct sctp_chunk {int /*<<< orphan*/  transport; TYPE_1__ subh; } ;
struct TYPE_4__ {int /*<<< orphan*/  tsn_map; } ;
struct sctp_association {TYPE_2__ peer; } ;
typedef  int /*<<< orphan*/  shut ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_CID_SHUTDOWN ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_shutdownhdr*) ; 
 struct sctp_chunk* sctp_make_control (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_tsnmap_get_ctsn (int /*<<< orphan*/ *) ; 

struct sctp_chunk *sctp_make_shutdown(const struct sctp_association *asoc,
				      const struct sctp_chunk *chunk)
{
	struct sctp_shutdownhdr shut;
	struct sctp_chunk *retval;
	__u32 ctsn;

	ctsn = sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map);
	shut.cum_tsn_ack = htonl(ctsn);

	retval = sctp_make_control(asoc, SCTP_CID_SHUTDOWN, 0,
				   sizeof(shut), GFP_ATOMIC);
	if (!retval)
		goto nodata;

	retval->subh.shutdown_hdr =
		sctp_addto_chunk(retval, sizeof(shut), &shut);

	if (chunk)
		retval->transport = chunk->transport;
nodata:
	return retval;
}