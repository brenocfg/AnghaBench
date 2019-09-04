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
struct sctp_transport {scalar_t__ dst_pending_confirm; int /*<<< orphan*/ * dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 

void sctp_transport_dst_release(struct sctp_transport *t)
{
	dst_release(t->dst);
	t->dst = NULL;
	t->dst_pending_confirm = 0;
}