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
struct TYPE_2__ {struct list_head* ns; scalar_t__ eof; } ;
struct tomoyo_io_buffer {scalar_t__ type; TYPE_1__ r; } ;
struct list_head {struct list_head* next; } ;

/* Variables and functions */
 scalar_t__ TOMOYO_EXCEPTIONPOLICY ; 
 scalar_t__ TOMOYO_PROFILE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct list_head tomoyo_namespace_list ; 

__attribute__((used)) static inline void tomoyo_set_namespace_cursor(struct tomoyo_io_buffer *head)
{
	struct list_head *ns;

	if (head->type != TOMOYO_EXCEPTIONPOLICY &&
	    head->type != TOMOYO_PROFILE)
		return;
	/*
	 * If this is the first read, or reading previous namespace finished
	 * and has more namespaces to read, update the namespace cursor.
	 */
	ns = head->r.ns;
	if (!ns || (head->r.eof && ns->next != &tomoyo_namespace_list)) {
		/* Clearing is OK because tomoyo_flush() returned true. */
		memset(&head->r, 0, sizeof(head->r));
		head->r.ns = ns ? ns->next : tomoyo_namespace_list.next;
	}
}