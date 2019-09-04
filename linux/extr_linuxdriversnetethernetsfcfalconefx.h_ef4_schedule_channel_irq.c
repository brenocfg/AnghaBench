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
struct ef4_channel {int /*<<< orphan*/  event_test_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_schedule_channel (struct ef4_channel*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

__attribute__((used)) static inline void ef4_schedule_channel_irq(struct ef4_channel *channel)
{
	channel->event_test_cpu = raw_smp_processor_id();
	ef4_schedule_channel(channel);
}