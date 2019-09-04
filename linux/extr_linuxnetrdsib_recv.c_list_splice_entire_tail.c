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
struct list_head {struct list_head* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  list_splice_tail (struct list_head*,struct list_head*) ; 

__attribute__((used)) static void list_splice_entire_tail(struct list_head *from,
				    struct list_head *to)
{
	struct list_head *from_last = from->prev;

	list_splice_tail(from_last, to);
	list_add_tail(from_last, to);
}