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
struct async_icount {scalar_t__ rng; scalar_t__ dsr; scalar_t__ dcd; scalar_t__ cts; } ;
struct fwtty_port {struct async_icount icount; } ;

/* Variables and functions */
 unsigned long TIOCM_CAR ; 
 unsigned long TIOCM_CTS ; 
 unsigned long TIOCM_DSR ; 
 unsigned long TIOCM_RNG ; 

__attribute__((used)) static int check_msr_delta(struct fwtty_port *port, unsigned long mask,
			   struct async_icount *prev)
{
	struct async_icount now;
	int delta;

	now = port->icount;

	delta = ((mask & TIOCM_RNG && prev->rng != now.rng) ||
		 (mask & TIOCM_DSR && prev->dsr != now.dsr) ||
		 (mask & TIOCM_CAR && prev->dcd != now.dcd) ||
		 (mask & TIOCM_CTS && prev->cts != now.cts));

	*prev = now;

	return delta;
}