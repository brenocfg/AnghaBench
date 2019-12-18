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
struct nr_sock {unsigned short vs; unsigned short va; scalar_t__ n2count; } ;

/* Variables and functions */
 int /*<<< orphan*/  nr_frames_acked (struct sock*,unsigned short) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  nr_start_t1timer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t1timer (struct sock*) ; 

void nr_check_iframes_acked(struct sock *sk, unsigned short nr)
{
	struct nr_sock *nrom = nr_sk(sk);

	if (nrom->vs == nr) {
		nr_frames_acked(sk, nr);
		nr_stop_t1timer(sk);
		nrom->n2count = 0;
	} else {
		if (nrom->va != nr) {
			nr_frames_acked(sk, nr);
			nr_start_t1timer(sk);
		}
	}
}