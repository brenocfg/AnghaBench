#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  canon_dir ;
struct TYPE_3__ {char const* new_dir; int /*<<< orphan*/  old_dir; struct TYPE_3__* next; } ;
typedef  TYPE_1__ TablespaceListCell ;
struct TYPE_4__ {TYPE_1__* head; } ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 TYPE_2__ tablespace_dirs ; 

__attribute__((used)) static const char *
get_tablespace_mapping(const char *dir)
{
	TablespaceListCell *cell;
	char		canon_dir[MAXPGPATH];

	/* Canonicalize path for comparison consistency */
	strlcpy(canon_dir, dir, sizeof(canon_dir));
	canonicalize_path(canon_dir);

	for (cell = tablespace_dirs.head; cell; cell = cell->next)
		if (strcmp(canon_dir, cell->old_dir) == 0)
			return cell->new_dir;

	return dir;
}