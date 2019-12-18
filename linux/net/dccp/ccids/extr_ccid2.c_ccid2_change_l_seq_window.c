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

/* Variables and functions */
 int /*<<< orphan*/  DCCPF_SEQUENCE_WINDOW ; 
 int /*<<< orphan*/  DCCPF_SEQ_WMAX ; 
 int /*<<< orphan*/  DCCPF_SEQ_WMIN ; 
 int /*<<< orphan*/  clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_feat_signal_nn_change (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccid2_change_l_seq_window(struct sock *sk, u64 val)
{
	dccp_feat_signal_nn_change(sk, DCCPF_SEQUENCE_WINDOW,
				   clamp_val(val, DCCPF_SEQ_WMIN,
						  DCCPF_SEQ_WMAX));
}