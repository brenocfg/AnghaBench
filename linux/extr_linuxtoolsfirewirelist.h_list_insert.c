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
struct list {struct list* prev; struct list* next; } ;

/* Variables and functions */

__attribute__((used)) static inline void
list_insert(struct list *link, struct list *new_link)
{
	new_link->prev		= link->prev;
	new_link->next		= link;
	new_link->prev->next	= new_link;
	new_link->next->prev	= new_link;
}