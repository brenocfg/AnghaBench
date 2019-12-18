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
struct sctp_stream {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_4__ {TYPE_1__* ext; } ;
struct TYPE_3__ {int /*<<< orphan*/  rr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__* SCTP_SO (struct sctp_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_sched_rr_init_sid(struct sctp_stream *stream, __u16 sid,
				  gfp_t gfp)
{
	INIT_LIST_HEAD(&SCTP_SO(stream, sid)->ext->rr_list);

	return 0;
}