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
struct sctp_ifwdtsn_skip {int /*<<< orphan*/  new_cum_tsn; } ;
struct sctp_ifwdtsn_hdr {int /*<<< orphan*/  new_cum_tsn; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifwdtsn_hdr; } ;
struct sctp_chunk {TYPE_1__ subh; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  skiplist ;
typedef  int /*<<< orphan*/  ftsn_hdr ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_CID_I_FWD_TSN ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,size_t,struct sctp_ifwdtsn_skip*) ; 
 struct sctp_chunk* sctp_make_control (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

struct sctp_chunk *sctp_make_ifwdtsn(const struct sctp_association *asoc,
				     __u32 new_cum_tsn, size_t nstreams,
				     struct sctp_ifwdtsn_skip *skiplist)
{
	struct sctp_chunk *retval = NULL;
	struct sctp_ifwdtsn_hdr ftsn_hdr;
	size_t hint;

	hint = (nstreams + 1) * sizeof(__u32);

	retval = sctp_make_control(asoc, SCTP_CID_I_FWD_TSN, 0, hint,
				   GFP_ATOMIC);
	if (!retval)
		return NULL;

	ftsn_hdr.new_cum_tsn = htonl(new_cum_tsn);
	retval->subh.ifwdtsn_hdr =
		sctp_addto_chunk(retval, sizeof(ftsn_hdr), &ftsn_hdr);

	sctp_addto_chunk(retval, nstreams * sizeof(skiplist[0]), skiplist);

	return retval;
}