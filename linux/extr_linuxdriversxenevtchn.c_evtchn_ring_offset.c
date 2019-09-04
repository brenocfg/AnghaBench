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
struct per_user_data {int ring_size; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int evtchn_ring_offset(struct per_user_data *u,
				       unsigned int idx)
{
	return idx & (u->ring_size - 1);
}