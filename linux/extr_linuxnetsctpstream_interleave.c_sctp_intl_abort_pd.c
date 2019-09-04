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
struct sctp_ulpq {TYPE_1__* asoc; } ;
struct sctp_stream_in {int /*<<< orphan*/  mid; scalar_t__ pd_mode; int /*<<< orphan*/  mid_uo; scalar_t__ pd_mode_uo; } ;
struct sctp_stream {scalar_t__ incnt; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  scalar_t__ __u16 ;
struct TYPE_2__ {struct sctp_stream stream; } ;

/* Variables and functions */
 struct sctp_stream_in* SCTP_SI (struct sctp_stream*,scalar_t__) ; 
 int /*<<< orphan*/  in ; 
 int /*<<< orphan*/  sctp_intl_reap_ordered (struct sctp_ulpq*,scalar_t__) ; 
 int /*<<< orphan*/  sctp_intl_stream_abort_pd (struct sctp_ulpq*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_mid_skip (struct sctp_stream*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpq_flush (struct sctp_ulpq*) ; 

__attribute__((used)) static void sctp_intl_abort_pd(struct sctp_ulpq *ulpq, gfp_t gfp)
{
	struct sctp_stream *stream = &ulpq->asoc->stream;
	__u16 sid;

	for (sid = 0; sid < stream->incnt; sid++) {
		struct sctp_stream_in *sin = SCTP_SI(stream, sid);
		__u32 mid;

		if (sin->pd_mode_uo) {
			sin->pd_mode_uo = 0;

			mid = sin->mid_uo;
			sctp_intl_stream_abort_pd(ulpq, sid, mid, 0x1, gfp);
		}

		if (sin->pd_mode) {
			sin->pd_mode = 0;

			mid = sin->mid;
			sctp_intl_stream_abort_pd(ulpq, sid, mid, 0, gfp);
			sctp_mid_skip(stream, in, sid, mid);

			sctp_intl_reap_ordered(ulpq, sid);
		}
	}

	/* intl abort pd happens only when all data needs to be cleaned */
	sctp_ulpq_flush(ulpq);
}