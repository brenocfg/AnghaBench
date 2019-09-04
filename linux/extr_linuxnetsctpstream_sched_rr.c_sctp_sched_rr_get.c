#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sctp_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */

__attribute__((used)) static int sctp_sched_rr_get(struct sctp_stream *stream, __u16 sid,
			     __u16 *value)
{
	return 0;
}