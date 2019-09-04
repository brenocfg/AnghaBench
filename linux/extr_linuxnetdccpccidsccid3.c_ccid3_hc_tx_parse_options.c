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
typedef  int u8 ;
struct sock {int dummy; } ;
struct ccid3_hc_tx_sock {int tx_x_recv; int /*<<< orphan*/  tx_p; } ;
typedef  int __be32 ;

/* Variables and functions */
 int DCCP_PKT_DATA ; 
 int /*<<< orphan*/  DCCP_WARN (char*,int /*<<< orphan*/ ,struct sock*,int,int) ; 
 int EINVAL ; 
#define  TFRC_OPT_LOSS_EVENT_RATE 129 
#define  TFRC_OPT_RECEIVE_RATE 128 
 struct ccid3_hc_tx_sock* ccid3_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,int /*<<< orphan*/ ,struct sock*,int) ; 
 int /*<<< orphan*/  dccp_role (struct sock*) ; 
 int /*<<< orphan*/  get_unaligned (int*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfrc_invert_loss_event_rate (int) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int ccid3_hc_tx_parse_options(struct sock *sk, u8 packet_type,
				     u8 option, u8 *optval, u8 optlen)
{
	struct ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	__be32 opt_val;

	switch (option) {
	case TFRC_OPT_RECEIVE_RATE:
	case TFRC_OPT_LOSS_EVENT_RATE:
		/* Must be ignored on Data packets, cf. RFC 4342 8.3 and 8.5 */
		if (packet_type == DCCP_PKT_DATA)
			break;
		if (unlikely(optlen != 4)) {
			DCCP_WARN("%s(%p), invalid len %d for %u\n",
				  dccp_role(sk), sk, optlen, option);
			return -EINVAL;
		}
		opt_val = ntohl(get_unaligned((__be32 *)optval));

		if (option == TFRC_OPT_RECEIVE_RATE) {
			/* Receive Rate is kept in units of 64 bytes/second */
			hc->tx_x_recv = opt_val;
			hc->tx_x_recv <<= 6;

			ccid3_pr_debug("%s(%p), RECEIVE_RATE=%u\n",
				       dccp_role(sk), sk, opt_val);
		} else {
			/* Update the fixpoint Loss Event Rate fraction */
			hc->tx_p = tfrc_invert_loss_event_rate(opt_val);

			ccid3_pr_debug("%s(%p), LOSS_EVENT_RATE=%u\n",
				       dccp_role(sk), sk, opt_val);
		}
	}
	return 0;
}