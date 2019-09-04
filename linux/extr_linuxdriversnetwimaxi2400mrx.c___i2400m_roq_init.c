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
struct i2400m_roq {int /*<<< orphan*/  queue; scalar_t__ ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void __i2400m_roq_init(struct i2400m_roq *roq)
{
	roq->ws = 0;
	skb_queue_head_init(&roq->queue);
}