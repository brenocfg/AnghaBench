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
struct snd_timer_user {int /*<<< orphan*/  qused; int /*<<< orphan*/  queue_size; int /*<<< orphan*/  qtail; int /*<<< orphan*/ * tqueue; int /*<<< orphan*/  overrun; } ;
struct snd_timer_tread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct snd_timer_tread*,int) ; 

__attribute__((used)) static void snd_timer_user_append_to_tqueue(struct snd_timer_user *tu,
					    struct snd_timer_tread *tread)
{
	if (tu->qused >= tu->queue_size) {
		tu->overrun++;
	} else {
		memcpy(&tu->tqueue[tu->qtail++], tread, sizeof(*tread));
		tu->qtail %= tu->queue_size;
		tu->qused++;
	}
}