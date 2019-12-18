#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct os_dirent {char* d_name; int /*<<< orphan*/  directory; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {struct os_dirent out; int /*<<< orphan*/  path; TYPE_2__* cur_dirent; int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ os_dir_t ;
struct TYPE_5__ {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  is_dir (int /*<<< orphan*/ ) ; 
 TYPE_2__* readdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

struct os_dirent *os_readdir(os_dir_t *dir)
{
	struct dstr file_path = {0};

	if (!dir)
		return NULL;

	dir->cur_dirent = readdir(dir->dir);
	if (!dir->cur_dirent)
		return NULL;

	strncpy(dir->out.d_name, dir->cur_dirent->d_name, 255);

	dstr_copy(&file_path, dir->path);
	dstr_cat(&file_path, "/");
	dstr_cat(&file_path, dir->out.d_name);

	dir->out.directory = is_dir(file_path.array);

	dstr_free(&file_path);

	return &dir->out;
}