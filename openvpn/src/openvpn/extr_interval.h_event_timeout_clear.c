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
struct event_timeout {int defined; scalar_t__ last; scalar_t__ n; } ;

/* Variables and functions */

__attribute__((used)) static inline void
event_timeout_clear(struct event_timeout *et)
{
    et->defined = false;
    et->n = 0;
    et->last = 0;
}