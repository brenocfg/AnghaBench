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
struct sock {int dummy; } ;
struct pep_sock {int /*<<< orphan*/  rx_fc; int /*<<< orphan*/  tx_fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PNS_PIPE_CREATED_IND ; 
 int /*<<< orphan*/  PN_PIPE_SB_NEGOTIATED_FC ; 
 int pep_indicate (struct sock*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pep_sb_size (int) ; 
 struct pep_sock* pep_sk (struct sock*) ; 

__attribute__((used)) static int pipe_handler_send_created_ind(struct sock *sk)
{
	struct pep_sock *pn = pep_sk(sk);
	u8 data[4] = {
		PN_PIPE_SB_NEGOTIATED_FC, pep_sb_size(2),
		pn->tx_fc, pn->rx_fc,
	};

	return pep_indicate(sk, PNS_PIPE_CREATED_IND, 1 /* sub-blocks */,
				data, 4, GFP_ATOMIC);
}