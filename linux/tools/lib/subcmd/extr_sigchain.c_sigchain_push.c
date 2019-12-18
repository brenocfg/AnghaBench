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
struct sigchain_signal {scalar_t__* old; int n; int /*<<< orphan*/  alloc; } ;
typedef  int /*<<< orphan*/  sigchain_fun ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  check_signum (int) ; 
 scalar_t__ signal (int,int /*<<< orphan*/ ) ; 
 struct sigchain_signal* signals ; 

__attribute__((used)) static int sigchain_push(int sig, sigchain_fun f)
{
	struct sigchain_signal *s = signals + sig;
	check_signum(sig);

	ALLOC_GROW(s->old, s->n + 1, s->alloc);
	s->old[s->n] = signal(sig, f);
	if (s->old[s->n] == SIG_ERR)
		return -1;
	s->n++;
	return 0;
}