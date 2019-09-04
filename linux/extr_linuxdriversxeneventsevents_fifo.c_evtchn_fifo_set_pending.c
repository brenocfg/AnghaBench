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
 int /*<<< orphan*/  BM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVTCHN_FIFO_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PENDING ; 
 int /*<<< orphan*/ * event_word_from_port (unsigned int) ; 
 int /*<<< orphan*/  sync_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void evtchn_fifo_set_pending(unsigned port)
{
	event_word_t *word = event_word_from_port(port);
	sync_set_bit(EVTCHN_FIFO_BIT(PENDING, word), BM(word));
}