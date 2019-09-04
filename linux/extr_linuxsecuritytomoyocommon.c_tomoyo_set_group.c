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
struct TYPE_2__ {int /*<<< orphan*/  acl_group_index; } ;
struct tomoyo_io_buffer {scalar_t__ type; TYPE_1__ r; } ;

/* Variables and functions */
 scalar_t__ TOMOYO_EXCEPTIONPOLICY ; 
 int /*<<< orphan*/  tomoyo_io_printf (struct tomoyo_io_buffer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_print_namespace (struct tomoyo_io_buffer*) ; 
 int /*<<< orphan*/  tomoyo_set_string (struct tomoyo_io_buffer*,char const*) ; 

__attribute__((used)) static void tomoyo_set_group(struct tomoyo_io_buffer *head,
			     const char *category)
{
	if (head->type == TOMOYO_EXCEPTIONPOLICY) {
		tomoyo_print_namespace(head);
		tomoyo_io_printf(head, "acl_group %u ",
				 head->r.acl_group_index);
	}
	tomoyo_set_string(head, category);
}