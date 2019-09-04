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
struct sock {int /*<<< orphan*/  sk_sndbuf; } ;
struct atm_vcc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atm_may_send (struct atm_vcc*,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 scalar_t__ sk_wmem_alloc_get (struct sock*) ; 

__attribute__((used)) static bool vcc_tx_ready(struct atm_vcc *vcc, unsigned int size)
{
	struct sock *sk = sk_atm(vcc);

	if (sk_wmem_alloc_get(sk) && !atm_may_send(vcc, size)) {
		pr_debug("Sorry: wmem_alloc = %d, size = %d, sndbuf = %d\n",
			 sk_wmem_alloc_get(sk), size, sk->sk_sndbuf);
		return false;
	}
	return true;
}