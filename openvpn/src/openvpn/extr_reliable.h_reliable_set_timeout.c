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
struct reliable {int /*<<< orphan*/  initial_timeout; } ;
typedef  int /*<<< orphan*/  interval_t ;

/* Variables and functions */

__attribute__((used)) static inline void
reliable_set_timeout(struct reliable *rel, interval_t timeout)
{
    rel->initial_timeout = timeout;
}