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
struct writequeue_entry {int offset; scalar_t__ len; scalar_t__ users; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_entry (struct writequeue_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void writequeue_entry_complete(struct writequeue_entry *e, int completed)
{
	e->offset += completed;
	e->len -= completed;

	if (e->len == 0 && e->users == 0) {
		list_del(&e->list);
		free_entry(e);
	}
}