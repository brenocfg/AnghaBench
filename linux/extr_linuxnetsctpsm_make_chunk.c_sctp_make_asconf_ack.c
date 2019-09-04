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
struct TYPE_2__ {int /*<<< orphan*/  addip_hdr; } ;
struct sctp_chunk {TYPE_1__ subh; } ;
struct sctp_association {int dummy; } ;
struct sctp_addiphdr {int /*<<< orphan*/  serial; } ;
typedef  int /*<<< orphan*/  asconf ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_CID_ASCONF_ACK ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_addiphdr*) ; 
 struct sctp_chunk* sctp_make_control (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_chunk *sctp_make_asconf_ack(const struct sctp_association *asoc,
					       __u32 serial, int vparam_len)
{
	struct sctp_addiphdr asconf;
	struct sctp_chunk *retval;
	int length = sizeof(asconf) + vparam_len;

	/* Create the chunk.  */
	retval = sctp_make_control(asoc, SCTP_CID_ASCONF_ACK, 0, length,
				   GFP_ATOMIC);
	if (!retval)
		return NULL;

	asconf.serial = htonl(serial);

	retval->subh.addip_hdr =
		sctp_addto_chunk(retval, sizeof(asconf), &asconf);

	return retval;
}