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
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dir_context {unsigned long long pos; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __putname (char*) ; 
 int /*<<< orphan*/  close_dir (void*) ; 
 char* dentry_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int,unsigned long long,unsigned int) ; 
 void* open_dir (char*,int*) ; 
 char* read_dir (void*,unsigned long long*,unsigned long long*,int*,unsigned int*) ; 
 int /*<<< orphan*/  seek_dir (void*,unsigned long long) ; 

__attribute__((used)) static int hostfs_readdir(struct file *file, struct dir_context *ctx)
{
	void *dir;
	char *name;
	unsigned long long next, ino;
	int error, len;
	unsigned int type;

	name = dentry_name(file->f_path.dentry);
	if (name == NULL)
		return -ENOMEM;
	dir = open_dir(name, &error);
	__putname(name);
	if (dir == NULL)
		return -error;
	next = ctx->pos;
	seek_dir(dir, next);
	while ((name = read_dir(dir, &next, &ino, &len, &type)) != NULL) {
		if (!dir_emit(ctx, name, len, ino, type))
			break;
		ctx->pos = next;
	}
	close_dir(dir);
	return 0;
}