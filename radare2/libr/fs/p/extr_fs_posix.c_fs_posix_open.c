#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  p; int /*<<< orphan*/ * ptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ RFSRoot ;
typedef  TYPE_2__ RFSFile ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_fs_file_free (TYPE_2__*) ; 
 TYPE_2__* r_fs_file_new (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * r_sandbox_fopen (char const*,char*) ; 

__attribute__((used)) static RFSFile* fs_posix_open(RFSRoot *root, const char *path, bool create) {
	FILE *fd;
	RFSFile *file = r_fs_file_new (root, path);
	if (!file) {
		return NULL;
	}
	file->ptr = NULL;
	file->p = root->p;
	fd = r_sandbox_fopen (path, create? "wb": "rb");
	if (fd) {
		fseek (fd, 0, SEEK_END);
		file->size = ftell (fd);
		fclose (fd);
	} else {
		r_fs_file_free (file);
		file = NULL;
	}
	return file;
}