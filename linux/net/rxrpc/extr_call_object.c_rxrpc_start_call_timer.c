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
struct TYPE_2__ {unsigned long expires; } ;
struct rxrpc_call {unsigned long ack_at; unsigned long ack_lost_at; unsigned long resend_at; unsigned long ping_at; unsigned long expect_rx_by; unsigned long expect_req_by; unsigned long expect_term_by; TYPE_1__ timer; } ;

/* Variables and functions */
 unsigned long MAX_JIFFY_OFFSET ; 
 unsigned long jiffies ; 

__attribute__((used)) static void rxrpc_start_call_timer(struct rxrpc_call *call)
{
	unsigned long now = jiffies;
	unsigned long j = now + MAX_JIFFY_OFFSET;

	call->ack_at = j;
	call->ack_lost_at = j;
	call->resend_at = j;
	call->ping_at = j;
	call->expect_rx_by = j;
	call->expect_req_by = j;
	call->expect_term_by = j;
	call->timer.expires = now;
}