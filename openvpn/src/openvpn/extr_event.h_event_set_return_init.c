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
struct event_set_return {int /*<<< orphan*/ * arg; scalar_t__ rwflags; } ;

/* Variables and functions */

__attribute__((used)) static inline void
event_set_return_init(struct event_set_return *esr)
{
    esr->rwflags = 0;
    esr->arg = NULL;
}