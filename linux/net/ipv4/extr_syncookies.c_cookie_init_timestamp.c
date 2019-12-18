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
typedef  int u64 ;
typedef  int u32 ;
struct request_sock {int dummy; } ;
struct inet_request_sock {int snd_wscale; scalar_t__ ecn_ok; scalar_t__ sack_ok; scalar_t__ wscale_ok; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int TCP_TS_HZ ; 
 int TSBITS ; 
 int TSMASK ; 
 int TS_OPT_ECN ; 
 int TS_OPT_SACK ; 
 int TS_OPT_WSCALE_MASK ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 int tcp_time_stamp_raw () ; 

u64 cookie_init_timestamp(struct request_sock *req)
{
	struct inet_request_sock *ireq;
	u32 ts, ts_now = tcp_time_stamp_raw();
	u32 options = 0;

	ireq = inet_rsk(req);

	options = ireq->wscale_ok ? ireq->snd_wscale : TS_OPT_WSCALE_MASK;
	if (ireq->sack_ok)
		options |= TS_OPT_SACK;
	if (ireq->ecn_ok)
		options |= TS_OPT_ECN;

	ts = ts_now & ~TSMASK;
	ts |= options;
	if (ts > ts_now) {
		ts >>= TSBITS;
		ts--;
		ts <<= TSBITS;
		ts |= options;
	}
	return (u64)ts * (NSEC_PER_SEC / TCP_TS_HZ);
}