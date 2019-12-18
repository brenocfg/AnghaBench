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
typedef  unsigned int u32 ;
struct sock {int dummy; } ;
struct inet_connection_sock {unsigned int icsk_pmtu_cookie; scalar_t__ icsk_ext_hdr_len; TYPE_1__* icsk_af_ops; } ;
struct dccp_sock {int dccps_send_ndp_count; unsigned int dccps_mss_cache; scalar_t__ dccps_hc_rx_ackvec; } ;
struct dccp_hdr_ext {int dummy; } ;
struct dccp_hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ net_header_len; } ;

/* Variables and functions */
 int DCCPAV_MIN_OPTLEN ; 
 unsigned int dccp_determine_ccmps (struct dccp_sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 scalar_t__ roundup (int,int) ; 

unsigned int dccp_sync_mss(struct sock *sk, u32 pmtu)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct dccp_sock *dp = dccp_sk(sk);
	u32 ccmps = dccp_determine_ccmps(dp);
	u32 cur_mps = ccmps ? min(pmtu, ccmps) : pmtu;

	/* Account for header lengths and IPv4/v6 option overhead */
	cur_mps -= (icsk->icsk_af_ops->net_header_len + icsk->icsk_ext_hdr_len +
		    sizeof(struct dccp_hdr) + sizeof(struct dccp_hdr_ext));

	/*
	 * Leave enough headroom for common DCCP header options.
	 * This only considers options which may appear on DCCP-Data packets, as
	 * per table 3 in RFC 4340, 5.8. When running out of space for other
	 * options (eg. Ack Vector which can take up to 255 bytes), it is better
	 * to schedule a separate Ack. Thus we leave headroom for the following:
	 *  - 1 byte for Slow Receiver (11.6)
	 *  - 6 bytes for Timestamp (13.1)
	 *  - 10 bytes for Timestamp Echo (13.3)
	 *  - 8 bytes for NDP count (7.7, when activated)
	 *  - 6 bytes for Data Checksum (9.3)
	 *  - %DCCPAV_MIN_OPTLEN bytes for Ack Vector size (11.4, when enabled)
	 */
	cur_mps -= roundup(1 + 6 + 10 + dp->dccps_send_ndp_count * 8 + 6 +
			   (dp->dccps_hc_rx_ackvec ? DCCPAV_MIN_OPTLEN : 0), 4);

	/* And store cached results */
	icsk->icsk_pmtu_cookie = pmtu;
	dp->dccps_mss_cache = cur_mps;

	return cur_mps;
}