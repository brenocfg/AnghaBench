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
struct sound_queue {scalar_t__ busy; int /*<<< orphan*/  sync_queue; int /*<<< orphan*/  open_queue; int /*<<< orphan*/  action_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void sq_init_waitqueue(struct sound_queue *sq)
{
	init_waitqueue_head(&sq->action_queue);
	init_waitqueue_head(&sq->open_queue);
	init_waitqueue_head(&sq->sync_queue);
	sq->busy = 0;
}