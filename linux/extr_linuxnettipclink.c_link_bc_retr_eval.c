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
typedef  void* u16 ;
struct tipc_link {void* prev_retr; void* prev_from; void* prev_to; } ;

/* Variables and functions */
 unsigned long TIPC_BC_RETR_LIMIT ; 
 void* jiffies ; 
 unsigned long jiffies_to_msecs (void*) ; 
 scalar_t__ less (void*,void*) ; 
 scalar_t__ more (void*,void*) ; 

__attribute__((used)) static bool link_bc_retr_eval(struct tipc_link *l, u16 *from, u16 *to)
{
	unsigned long elapsed = jiffies_to_msecs(jiffies - l->prev_retr);

	if (less(*to, *from))
		return false;

	/* New retransmission request */
	if ((elapsed > TIPC_BC_RETR_LIMIT) ||
	    less(*to, l->prev_from) || more(*from, l->prev_to)) {
		l->prev_from = *from;
		l->prev_to = *to;
		l->prev_retr = jiffies;
		return true;
	}

	/* Inside range of previous retransmit */
	if (!less(*from, l->prev_from) && !more(*to, l->prev_to))
		return false;

	/* Fully or partially outside previous range => exclude overlap */
	if (less(*from, l->prev_from)) {
		*to = l->prev_from - 1;
		l->prev_from = *from;
	}
	if (more(*to, l->prev_to)) {
		*from = l->prev_to + 1;
		l->prev_to = *to;
	}
	l->prev_retr = jiffies;
	return true;
}