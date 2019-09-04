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
 unsigned int EVENT_WORDS_PER_PAGE ; 
 int EVTCHN_FIFO_MASKED ; 

__attribute__((used)) static void init_array_page(event_word_t *array_page)
{
	unsigned i;

	for (i = 0; i < EVENT_WORDS_PER_PAGE; i++)
		array_page[i] = 1 << EVTCHN_FIFO_MASKED;
}