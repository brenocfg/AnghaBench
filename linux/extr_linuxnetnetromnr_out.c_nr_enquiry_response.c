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
struct sock {int dummy; } ;
struct nr_sock {int condition; int /*<<< orphan*/  vr; int /*<<< orphan*/  vl; int /*<<< orphan*/  reseq_queue; } ;

/* Variables and functions */
 int NR_CHOKE_FLAG ; 
 int NR_COND_ACK_PENDING ; 
 int NR_COND_OWN_RX_BUSY ; 
 int NR_INFOACK ; 
 int NR_NAK_FLAG ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  nr_write_internal (struct sock*,int) ; 
 int /*<<< orphan*/ * skb_peek (int /*<<< orphan*/ *) ; 

void nr_enquiry_response(struct sock *sk)
{
	struct nr_sock *nr = nr_sk(sk);
	int frametype = NR_INFOACK;

	if (nr->condition & NR_COND_OWN_RX_BUSY) {
		frametype |= NR_CHOKE_FLAG;
	} else {
		if (skb_peek(&nr->reseq_queue) != NULL)
			frametype |= NR_NAK_FLAG;
	}

	nr_write_internal(sk, frametype);

	nr->vl         = nr->vr;
	nr->condition &= ~NR_COND_ACK_PENDING;
}