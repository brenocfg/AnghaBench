#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ action; int type; int /*<<< orphan*/  link_target; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ file_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FILE_ACTION_CREATE ; 
#define  FILE_TYPE_DIRECTORY 130 
#define  FILE_TYPE_REGULAR 129 
#define  FILE_TYPE_SYMLINK 128 
 int /*<<< orphan*/  create_target_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_target_symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*) ; 

void
create_target(file_entry_t *entry)
{
	Assert(entry->action == FILE_ACTION_CREATE);

	switch (entry->type)
	{
		case FILE_TYPE_DIRECTORY:
			create_target_dir(entry->path);
			break;

		case FILE_TYPE_SYMLINK:
			create_target_symlink(entry->path, entry->link_target);
			break;

		case FILE_TYPE_REGULAR:
			/* can't happen. Regular files are created with open_target_file. */
			pg_fatal("invalid action (CREATE) for regular file");
			break;
	}
}