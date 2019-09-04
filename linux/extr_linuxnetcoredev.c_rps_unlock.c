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
struct softnet_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void rps_unlock(struct softnet_data *sd)
{
#ifdef CONFIG_RPS
	spin_unlock(&sd->input_pkt_queue.lock);
#endif
}