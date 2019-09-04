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
struct cxgbi_sock {unsigned int write_seq; unsigned int snd_nxt; unsigned int snd_una; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTP_ESTABLISHED ; 
 int /*<<< orphan*/  cxgbi_sock_set_state (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_confirm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

void cxgbi_sock_established(struct cxgbi_sock *csk, unsigned int snd_isn,
			unsigned int opt)
{
	csk->write_seq = csk->snd_nxt = csk->snd_una = snd_isn;
	dst_confirm(csk->dst);
	smp_mb();
	cxgbi_sock_set_state(csk, CTP_ESTABLISHED);
}