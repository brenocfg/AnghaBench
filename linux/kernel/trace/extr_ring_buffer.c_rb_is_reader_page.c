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
struct list_head {int /*<<< orphan*/  next; } ;
struct TYPE_2__ {struct list_head* prev; } ;
struct buffer_page {TYPE_1__ list; } ;

/* Variables and functions */
 TYPE_1__* rb_list_head (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rb_is_reader_page(struct buffer_page *page)
{
	struct list_head *list = page->list.prev;

	return rb_list_head(list->next) != &page->list;
}