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
struct nr_sock {unsigned short va; unsigned short vs; } ;

/* Variables and functions */
 unsigned short NR_MODULUS ; 
 struct nr_sock* nr_sk (struct sock*) ; 

int nr_validate_nr(struct sock *sk, unsigned short nr)
{
	struct nr_sock *nrom = nr_sk(sk);
	unsigned short vc = nrom->va;

	while (vc != nrom->vs) {
		if (nr == vc) return 1;
		vc = (vc + 1) % NR_MODULUS;
	}

	return nr == nrom->vs;
}