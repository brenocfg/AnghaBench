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
struct ceph_x_ticket_handler {scalar_t__ renew_after; int /*<<< orphan*/  have_key; } ;

/* Variables and functions */
 scalar_t__ ktime_get_real_seconds () ; 

__attribute__((used)) static bool need_key(struct ceph_x_ticket_handler *th)
{
	if (!th->have_key)
		return true;

	return ktime_get_real_seconds() >= th->renew_after;
}