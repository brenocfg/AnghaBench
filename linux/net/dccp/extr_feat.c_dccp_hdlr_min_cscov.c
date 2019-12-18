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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct sock {int dummy; } ;
struct dccp_sock {scalar_t__ dccps_pcslen; scalar_t__ dccps_pcrlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_WARN (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

__attribute__((used)) static int dccp_hdlr_min_cscov(struct sock *sk, u64 cscov, bool rx)
{
	struct dccp_sock *dp = dccp_sk(sk);

	if (rx)
		dp->dccps_pcrlen = cscov;
	else {
		if (dp->dccps_pcslen == 0)
			dp->dccps_pcslen = cscov;
		else if (cscov > dp->dccps_pcslen)
			DCCP_WARN("CsCov %u too small, peer requires >= %u\n",
				  dp->dccps_pcslen, (u8)cscov);
	}
	return 0;
}