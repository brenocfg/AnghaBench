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
struct sctp_stream_in {scalar_t__ pd_mode; scalar_t__ pd_mode_uo; int /*<<< orphan*/  mid_uo; } ;
struct sctp_stream {int dummy; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {struct sctp_stream stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MID_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCTP_FTSN_U_BIT ; 
 int /*<<< orphan*/  in ; 
 int /*<<< orphan*/  sctp_intl_reap_ordered (struct sctp_ulpq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_intl_stream_abort_pd (struct sctp_ulpq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_mid_peek (struct sctp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_mid_skip (struct sctp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_stream_in* sctp_stream_in (struct sctp_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_intl_skip(struct sctp_ulpq *ulpq, __u16 sid, __u32 mid,
			   __u8 flags)
{
	struct sctp_stream_in *sin = sctp_stream_in(&ulpq->asoc->stream, sid);
	struct sctp_stream *stream  = &ulpq->asoc->stream;

	if (flags & SCTP_FTSN_U_BIT) {
		if (sin->pd_mode_uo && MID_lt(sin->mid_uo, mid)) {
			sin->pd_mode_uo = 0;
			sctp_intl_stream_abort_pd(ulpq, sid, mid, 0x1,
						  GFP_ATOMIC);
		}
		return;
	}

	if (MID_lt(mid, sctp_mid_peek(stream, in, sid)))
		return;

	if (sin->pd_mode) {
		sin->pd_mode = 0;
		sctp_intl_stream_abort_pd(ulpq, sid, mid, 0x0, GFP_ATOMIC);
	}

	sctp_mid_skip(stream, in, sid, mid);

	sctp_intl_reap_ordered(ulpq, sid);
}