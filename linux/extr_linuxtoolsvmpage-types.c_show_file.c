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
struct stat {unsigned long long st_size; long st_atime; long st_mtime; scalar_t__ st_ino; } ;
typedef  int /*<<< orphan*/  mtime ;
typedef  int /*<<< orphan*/  atime ;

/* Variables and functions */
 int /*<<< orphan*/  localtime (long*) ; 
 unsigned long long page_size ; 
 int /*<<< orphan*/  printf (char*,char const*,long,...) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 long time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void show_file(const char *name, const struct stat *st)
{
	unsigned long long size = st->st_size;
	char atime[64], mtime[64];
	long now = time(NULL);

	printf("%s\tInode: %u\tSize: %llu (%llu pages)\n",
			name, (unsigned)st->st_ino,
			size, (size + page_size - 1) / page_size);

	strftime(atime, sizeof(atime), "%c", localtime(&st->st_atime));
	strftime(mtime, sizeof(mtime), "%c", localtime(&st->st_mtime));

	printf("Modify: %s (%ld seconds ago)\nAccess: %s (%ld seconds ago)\n",
			mtime, now - st->st_mtime,
			atime, now - st->st_atime);
}