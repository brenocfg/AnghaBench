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
typedef  int u8 ;
struct request_sock {int const num_timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  acked; } ;

/* Variables and functions */
 TYPE_1__* inet_rsk (struct request_sock*) ; 

__attribute__((used)) static inline void syn_ack_recalc(struct request_sock *req, const int thresh,
				  const int max_retries,
				  const u8 rskq_defer_accept,
				  int *expire, int *resend)
{
	if (!rskq_defer_accept) {
		*expire = req->num_timeout >= thresh;
		*resend = 1;
		return;
	}
	*expire = req->num_timeout >= thresh &&
		  (!inet_rsk(req)->acked || req->num_timeout >= max_retries);
	/*
	 * Do not resend while waiting for data after ACK,
	 * start to resend on end of deferring period to give
	 * last chance for data or ACK to create established socket.
	 */
	*resend = !inet_rsk(req)->acked ||
		  req->num_timeout >= rskq_defer_accept - 1;
}