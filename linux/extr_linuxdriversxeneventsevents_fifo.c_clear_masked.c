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
typedef  int event_word_t ;

/* Variables and functions */
 int EVTCHN_FIFO_BUSY ; 
 int EVTCHN_FIFO_MASKED ; 
 int sync_cmpxchg (int volatile*,int,int) ; 

__attribute__((used)) static void clear_masked(volatile event_word_t *word)
{
	event_word_t new, old, w;

	w = *word;

	do {
		old = w & ~(1 << EVTCHN_FIFO_BUSY);
		new = old & ~(1 << EVTCHN_FIFO_MASKED);
		w = sync_cmpxchg(word, old, new);
	} while (w != old);
}