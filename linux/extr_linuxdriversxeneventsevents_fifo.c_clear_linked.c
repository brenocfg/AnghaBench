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
typedef  int uint32_t ;
typedef  int event_word_t ;

/* Variables and functions */
 int EVTCHN_FIFO_LINKED ; 
 int EVTCHN_FIFO_LINK_MASK ; 
 int sync_cmpxchg (int volatile*,int,int) ; 

__attribute__((used)) static uint32_t clear_linked(volatile event_word_t *word)
{
	event_word_t new, old, w;

	w = *word;

	do {
		old = w;
		new = (w & ~((1 << EVTCHN_FIFO_LINKED)
			     | EVTCHN_FIFO_LINK_MASK));
	} while ((w = sync_cmpxchg(word, old, new)) != old);

	return w & EVTCHN_FIFO_LINK_MASK;
}