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
struct x25_neigh {int /*<<< orphan*/  t20timer; } ;

/* Variables and functions */
 int timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int x25_t20timer_pending(struct x25_neigh *nb)
{
	return timer_pending(&nb->t20timer);
}