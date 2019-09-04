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
struct TimeoutEntry {scalar_t__ prev; scalar_t__ next; } ;

/* Variables and functions */

__attribute__((used)) static inline void
timeout_init(struct TimeoutEntry *entry)
{
    entry->next = 0;
    entry->prev = 0;
}