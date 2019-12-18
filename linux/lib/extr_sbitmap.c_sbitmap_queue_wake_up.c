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
struct sbitmap_queue {int dummy; } ;

/* Variables and functions */
 scalar_t__ __sbq_wake_up (struct sbitmap_queue*) ; 

void sbitmap_queue_wake_up(struct sbitmap_queue *sbq)
{
	while (__sbq_wake_up(sbq))
		;
}