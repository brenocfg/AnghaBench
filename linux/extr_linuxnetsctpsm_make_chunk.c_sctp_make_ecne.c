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
struct sctp_ecnehdr {int /*<<< orphan*/  lowest_tsn; } ;
struct TYPE_2__ {int /*<<< orphan*/  ecne_hdr; } ;
struct sctp_chunk {TYPE_1__ subh; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  ecne ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_CID_ECN_ECNE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_ecnehdr*) ; 
 struct sctp_chunk* sctp_make_control (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct sctp_chunk *sctp_make_ecne(const struct sctp_association *asoc,
				  const __u32 lowest_tsn)
{
	struct sctp_chunk *retval;
	struct sctp_ecnehdr ecne;

	ecne.lowest_tsn = htonl(lowest_tsn);
	retval = sctp_make_control(asoc, SCTP_CID_ECN_ECNE, 0,
				   sizeof(ecne), GFP_ATOMIC);
	if (!retval)
		goto nodata;
	retval->subh.ecne_hdr =
		sctp_addto_chunk(retval, sizeof(ecne), &ecne);

nodata:
	return retval;
}