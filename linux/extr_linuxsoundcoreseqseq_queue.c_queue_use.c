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
struct snd_seq_queue {int clients; int /*<<< orphan*/  timer; int /*<<< orphan*/  clients_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_seq_timer_close (struct snd_seq_queue*) ; 
 int /*<<< orphan*/  snd_seq_timer_defaults (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_timer_open (struct snd_seq_queue*) ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void queue_use(struct snd_seq_queue *queue, int client, int use)
{
	if (use) {
		if (!test_and_set_bit(client, queue->clients_bitmap))
			queue->clients++;
	} else {
		if (test_and_clear_bit(client, queue->clients_bitmap))
			queue->clients--;
	}
	if (queue->clients) {
		if (use && queue->clients == 1)
			snd_seq_timer_defaults(queue->timer);
		snd_seq_timer_open(queue);
	} else {
		snd_seq_timer_close(queue);
	}
}