#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tail; scalar_t__ head; } ;
struct rrdengine_worker_config {int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  cmd_cond; scalar_t__ queue_size; TYPE_1__ cmd_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ uv_cond_init (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_mutex_init (int /*<<< orphan*/ *) ; 

void rrdeng_init_cmd_queue(struct rrdengine_worker_config* wc)
{
    wc->cmd_queue.head = wc->cmd_queue.tail = 0;
    wc->queue_size = 0;
    assert(0 == uv_cond_init(&wc->cmd_cond));
    assert(0 == uv_mutex_init(&wc->cmd_mutex));
}