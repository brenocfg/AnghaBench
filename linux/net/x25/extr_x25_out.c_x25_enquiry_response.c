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
struct x25_sock {int condition; int /*<<< orphan*/  vr; int /*<<< orphan*/  vl; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int X25_COND_ACK_PENDING ; 
 int X25_COND_OWN_RX_BUSY ; 
 int /*<<< orphan*/  X25_RNR ; 
 int /*<<< orphan*/  X25_RR ; 
 struct x25_sock* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_stop_timer (struct sock*) ; 
 int /*<<< orphan*/  x25_write_internal (struct sock*,int /*<<< orphan*/ ) ; 

void x25_enquiry_response(struct sock *sk)
{
	struct x25_sock *x25 = x25_sk(sk);

	if (x25->condition & X25_COND_OWN_RX_BUSY)
		x25_write_internal(sk, X25_RNR);
	else
		x25_write_internal(sk, X25_RR);

	x25->vl         = x25->vr;
	x25->condition &= ~X25_COND_ACK_PENDING;

	x25_stop_timer(sk);
}