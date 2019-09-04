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
typedef  int /*<<< orphan*/  event_word_t ;

/* Variables and functions */
 unsigned int EVENT_WORDS_PER_PAGE ; 
 int /*<<< orphan*/ ** event_array ; 

__attribute__((used)) static inline event_word_t *event_word_from_port(unsigned port)
{
	unsigned i = port / EVENT_WORDS_PER_PAGE;

	return event_array[i] + port % EVENT_WORDS_PER_PAGE;
}