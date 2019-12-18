#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ outcnt; } ;
struct TYPE_8__ {TYPE_1__* sched; } ;
struct sctp_association {TYPE_3__ stream; TYPE_2__ outqueue; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ __u16 ;
struct TYPE_10__ {int /*<<< orphan*/  ext; } ;
struct TYPE_7__ {int (* set ) (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_5__* SCTP_SO (TYPE_3__*,scalar_t__) ; 
 int sctp_stream_init_ext (TYPE_3__*,scalar_t__) ; 
 int stub1 (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int sctp_sched_set_value(struct sctp_association *asoc, __u16 sid,
			 __u16 value, gfp_t gfp)
{
	if (sid >= asoc->stream.outcnt)
		return -EINVAL;

	if (!SCTP_SO(&asoc->stream, sid)->ext) {
		int ret;

		ret = sctp_stream_init_ext(&asoc->stream, sid);
		if (ret)
			return ret;
	}

	return asoc->outqueue.sched->set(&asoc->stream, sid, value, gfp);
}