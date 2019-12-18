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
struct sctp_sndrcvinfo {int sinfo_flags; int /*<<< orphan*/  sinfo_stream; } ;
struct sctp_idatahdr {int /*<<< orphan*/  stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  idata_hdr; } ;
struct sctp_chunk {int /*<<< orphan*/  sinfo; TYPE_1__ subh; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dp ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DATA_UNORDERED ; 
 int SCTP_UNORDERED ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sctp_sndrcvinfo const*,int) ; 
 int /*<<< orphan*/  memset (struct sctp_idatahdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_idatahdr*) ; 
 struct sctp_chunk* sctp_make_idata (struct sctp_association const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_chunk *sctp_make_idatafrag_empty(
					const struct sctp_association *asoc,
					const struct sctp_sndrcvinfo *sinfo,
					int len, __u8 flags, gfp_t gfp)
{
	struct sctp_chunk *retval;
	struct sctp_idatahdr dp;

	memset(&dp, 0, sizeof(dp));
	dp.stream = htons(sinfo->sinfo_stream);

	if (sinfo->sinfo_flags & SCTP_UNORDERED)
		flags |= SCTP_DATA_UNORDERED;

	retval = sctp_make_idata(asoc, flags, sizeof(dp) + len, gfp);
	if (!retval)
		return NULL;

	retval->subh.idata_hdr = sctp_addto_chunk(retval, sizeof(dp), &dp);
	memcpy(&retval->sinfo, sinfo, sizeof(struct sctp_sndrcvinfo));

	return retval;
}