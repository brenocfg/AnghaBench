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
typedef  int /*<<< orphan*/  time_t ;
struct event_timeout {int defined; int /*<<< orphan*/  last; scalar_t__ n; } ;
typedef  scalar_t__ interval_t ;

/* Variables and functions */

__attribute__((used)) static inline void
event_timeout_init(struct event_timeout *et, interval_t n, const time_t local_now)
{
    et->defined = true;
    et->n = (n >= 0) ? n : 0;
    et->last = local_now;
}