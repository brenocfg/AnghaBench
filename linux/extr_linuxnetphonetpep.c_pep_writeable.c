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
struct pep_sock {int /*<<< orphan*/  tx_credits; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct pep_sock* pep_sk (struct sock*) ; 

int pep_writeable(struct sock *sk)
{
	struct pep_sock *pn = pep_sk(sk);

	return atomic_read(&pn->tx_credits);
}