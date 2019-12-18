#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TimeoutEntry {scalar_t__ timestamp; TYPE_1__** prev; TYPE_1__* next; } ;
struct TYPE_2__ {struct TYPE_2__** prev; } ;

/* Variables and functions */

__attribute__((used)) static inline void
timeout_unlink(struct TimeoutEntry *entry)
{
    if (entry->prev == 0 && entry->next == 0)
        return;
    *(entry->prev) = entry->next;
    if (entry->next)
        entry->next->prev = entry->prev;
    entry->next = 0;
    entry->prev = 0;
    entry->timestamp = 0;
}