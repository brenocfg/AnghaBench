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
struct clip_vcc {struct clip_vcc* next; scalar_t__ xoff; struct atmarp_entry* entry; } ;
struct atmarp_entry {TYPE_1__* neigh; struct clip_vcc* vccs; } ;
struct TYPE_2__ {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_debug (char*,struct clip_vcc*,struct atmarp_entry*,TYPE_1__*) ; 

__attribute__((used)) static void link_vcc(struct clip_vcc *clip_vcc, struct atmarp_entry *entry)
{
	pr_debug("%p to entry %p (neigh %p)\n", clip_vcc, entry, entry->neigh);
	clip_vcc->entry = entry;
	clip_vcc->xoff = 0;	/* @@@ may overrun buffer by one packet */
	clip_vcc->next = entry->vccs;
	entry->vccs = clip_vcc;
	entry->neigh->used = jiffies;
}