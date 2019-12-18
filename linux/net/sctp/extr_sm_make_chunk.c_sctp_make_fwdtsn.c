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
struct sctp_fwdtsn_skip {int /*<<< orphan*/  ssn; int /*<<< orphan*/  stream; int /*<<< orphan*/  new_cum_tsn; } ;
struct sctp_fwdtsn_hdr {int /*<<< orphan*/  ssn; int /*<<< orphan*/  stream; int /*<<< orphan*/  new_cum_tsn; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwdtsn_hdr; } ;
struct sctp_chunk {TYPE_1__ subh; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  skip ;
typedef  int /*<<< orphan*/  ftsn_hdr ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_CID_FWD_TSN ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_fwdtsn_skip*) ; 
 struct sctp_chunk* sctp_make_control (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

struct sctp_chunk *sctp_make_fwdtsn(const struct sctp_association *asoc,
				    __u32 new_cum_tsn, size_t nstreams,
				    struct sctp_fwdtsn_skip *skiplist)
{
	struct sctp_chunk *retval = NULL;
	struct sctp_fwdtsn_hdr ftsn_hdr;
	struct sctp_fwdtsn_skip skip;
	size_t hint;
	int i;

	hint = (nstreams + 1) * sizeof(__u32);

	retval = sctp_make_control(asoc, SCTP_CID_FWD_TSN, 0, hint, GFP_ATOMIC);

	if (!retval)
		return NULL;

	ftsn_hdr.new_cum_tsn = htonl(new_cum_tsn);
	retval->subh.fwdtsn_hdr =
		sctp_addto_chunk(retval, sizeof(ftsn_hdr), &ftsn_hdr);

	for (i = 0; i < nstreams; i++) {
		skip.stream = skiplist[i].stream;
		skip.ssn = skiplist[i].ssn;
		sctp_addto_chunk(retval, sizeof(skip), &skip);
	}

	return retval;
}