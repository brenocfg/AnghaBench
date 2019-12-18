#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer_per_cpu {unsigned long nr_pages; int /*<<< orphan*/  pages; int /*<<< orphan*/  cpu; } ;
struct TYPE_5__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_HEAD (TYPE_1__) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __rb_allocate_pages (unsigned long,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*) ; 
 TYPE_1__ pages ; 
 int /*<<< orphan*/  rb_check_pages (struct ring_buffer_per_cpu*) ; 

__attribute__((used)) static int rb_allocate_pages(struct ring_buffer_per_cpu *cpu_buffer,
			     unsigned long nr_pages)
{
	LIST_HEAD(pages);

	WARN_ON(!nr_pages);

	if (__rb_allocate_pages(nr_pages, &pages, cpu_buffer->cpu))
		return -ENOMEM;

	/*
	 * The ring buffer page list is a circular list that does not
	 * start and end with a list head. All page list items point to
	 * other pages.
	 */
	cpu_buffer->pages = pages.next;
	list_del(&pages);

	cpu_buffer->nr_pages = nr_pages;

	rb_check_pages(cpu_buffer);

	return 0;
}