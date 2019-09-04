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
struct list_entry {struct list_entry* prev; struct list_entry* next; } ;

/* Variables and functions */

__attribute__((used)) static void list_add(
    struct list_entry *entry,
    struct list_entry *prev,
    struct list_entry *next)
{
    /* assert(prev->next == next && next->prev == prev); */
    entry->prev = prev;
    entry->next = next;
    prev->next = entry;
    next->prev = entry;
}