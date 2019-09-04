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
struct ceph_x_ticket_handler {int have_key; scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ ktime_get_real_seconds () ; 

__attribute__((used)) static bool have_key(struct ceph_x_ticket_handler *th)
{
	if (th->have_key) {
		if (ktime_get_real_seconds() >= th->expires)
			th->have_key = false;
	}

	return th->have_key;
}