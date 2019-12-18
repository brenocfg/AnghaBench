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
typedef  int /*<<< orphan*/  u64 ;
struct sock {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_gss; int /*<<< orphan*/  dccps_awh; int /*<<< orphan*/  dccps_iss; int /*<<< orphan*/  dccps_awl; int /*<<< orphan*/  dccps_l_seq_win; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD48 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUB48 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ before48 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

__attribute__((used)) static inline void dccp_update_gss(struct sock *sk, u64 seq)
{
	struct dccp_sock *dp = dccp_sk(sk);

	dp->dccps_gss = seq;
	/* Ack validity window depends on local Sequence Window value (7.5.1) */
	dp->dccps_awl = SUB48(ADD48(dp->dccps_gss, 1), dp->dccps_l_seq_win);
	/* Adjust AWL so that it is not below ISS - see comment above for SWL */
	if (before48(dp->dccps_awl, dp->dccps_iss))
		dp->dccps_awl = dp->dccps_iss;
	dp->dccps_awh = dp->dccps_gss;
}