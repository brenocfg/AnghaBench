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
struct TYPE_2__ {int /*<<< orphan*/  is_delete; } ;
struct tomoyo_io_buffer {char* write_buf; TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int tomoyo_manage_by_non_root ; 
 int tomoyo_update_manager_entry (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tomoyo_write_manager(struct tomoyo_io_buffer *head)
{
	char *data = head->write_buf;

	if (!strcmp(data, "manage_by_non_root")) {
		tomoyo_manage_by_non_root = !head->w.is_delete;
		return 0;
	}
	return tomoyo_update_manager_entry(data, head->w.is_delete);
}