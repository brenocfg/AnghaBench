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
struct os_dir {char const* path; int /*<<< orphan*/ * dir; } ;
typedef  struct os_dir os_dir_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 struct os_dir* bzalloc (int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 

os_dir_t *os_opendir(const char *path)
{
	struct os_dir *dir;
	DIR *dir_val;

	dir_val = opendir(path);
	if (!dir_val)
		return NULL;

	dir = bzalloc(sizeof(struct os_dir));
	dir->dir = dir_val;
	dir->path = path;
	return dir;
}