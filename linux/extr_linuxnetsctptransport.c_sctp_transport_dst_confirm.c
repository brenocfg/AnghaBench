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
struct sctp_transport {int dst_pending_confirm; } ;

/* Variables and functions */

void sctp_transport_dst_confirm(struct sctp_transport *t)
{
	t->dst_pending_confirm = 1;
}