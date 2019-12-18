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
struct nr_sock {int condition; scalar_t__ n2count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_CONNREQ ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  nr_start_t1timer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_idletimer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t2timer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t4timer (struct sock*) ; 
 int /*<<< orphan*/  nr_write_internal (struct sock*,int /*<<< orphan*/ ) ; 

void nr_establish_data_link(struct sock *sk)
{
	struct nr_sock *nr = nr_sk(sk);

	nr->condition = 0x00;
	nr->n2count   = 0;

	nr_write_internal(sk, NR_CONNREQ);

	nr_stop_t2timer(sk);
	nr_stop_t4timer(sk);
	nr_stop_idletimer(sk);
	nr_start_t1timer(sk);
}