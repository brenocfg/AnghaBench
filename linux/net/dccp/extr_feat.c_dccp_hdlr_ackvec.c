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
typedef  scalar_t__ u64 ;
struct sock {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/ * dccps_hc_rx_ackvec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * dccp_ackvec_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_ackvec_free (int /*<<< orphan*/ *) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  gfp_any () ; 

__attribute__((used)) static int dccp_hdlr_ackvec(struct sock *sk, u64 enable, bool rx)
{
	struct dccp_sock *dp = dccp_sk(sk);

	if (rx) {
		if (enable && dp->dccps_hc_rx_ackvec == NULL) {
			dp->dccps_hc_rx_ackvec = dccp_ackvec_alloc(gfp_any());
			if (dp->dccps_hc_rx_ackvec == NULL)
				return -ENOMEM;
		} else if (!enable) {
			dccp_ackvec_free(dp->dccps_hc_rx_ackvec);
			dp->dccps_hc_rx_ackvec = NULL;
		}
	}
	return 0;
}