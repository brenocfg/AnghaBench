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
struct stat {int st_mode; int st_nlink; int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 int ENOENT ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  memfd_content ; 
 char* memfd_path ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int memfd_getattr(const char *path, struct stat *st)
{
	memset(st, 0, sizeof(*st));

	if (!strcmp(path, "/")) {
		st->st_mode = S_IFDIR | 0755;
		st->st_nlink = 2;
	} else if (!strcmp(path, memfd_path)) {
		st->st_mode = S_IFREG | 0444;
		st->st_nlink = 1;
		st->st_size = strlen(memfd_content);
	} else {
		return -ENOENT;
	}

	return 0;
}