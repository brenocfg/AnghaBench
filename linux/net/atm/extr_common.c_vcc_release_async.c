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
struct sock {int sk_err; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_shutdown; } ;
struct atm_vcc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_CLOSE ; 
 int /*<<< orphan*/  ATM_VF_WAITING ; 
 int /*<<< orphan*/  RCV_SHUTDOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

void vcc_release_async(struct atm_vcc *vcc, int reply)
{
	struct sock *sk = sk_atm(vcc);

	set_bit(ATM_VF_CLOSE, &vcc->flags);
	sk->sk_shutdown |= RCV_SHUTDOWN;
	sk->sk_err = -reply;
	clear_bit(ATM_VF_WAITING, &vcc->flags);
	sk->sk_state_change(sk);
}