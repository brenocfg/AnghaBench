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
struct dirent {int d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
#define  DT_DIR 130 
#define  DT_LNK 129 
#define  DT_REG 128 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dirfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f_lnk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_reg_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * fdopendir (int) ; 
 int openat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int streq (int /*<<< orphan*/ ,char*) ; 
 struct dirent* xreaddir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void f(DIR *d, unsigned int level)
{
	struct dirent *de;

	de = xreaddir(d);
	assert(de->d_type == DT_DIR);
	assert(streq(de->d_name, "."));

	de = xreaddir(d);
	assert(de->d_type == DT_DIR);
	assert(streq(de->d_name, ".."));

	while ((de = xreaddir(d))) {
		assert(!streq(de->d_name, "."));
		assert(!streq(de->d_name, ".."));

		switch (de->d_type) {
			DIR *dd;
			int fd;

		case DT_REG:
			if (level == 0 && streq(de->d_name, "sysrq-trigger")) {
				f_reg_write(d, de->d_name, "h", 1);
			} else if (level == 1 && streq(de->d_name, "clear_refs")) {
				f_reg_write(d, de->d_name, "1", 1);
			} else if (level == 3 && streq(de->d_name, "clear_refs")) {
				f_reg_write(d, de->d_name, "1", 1);
			} else {
				f_reg(d, de->d_name);
			}
			break;
		case DT_DIR:
			fd = openat(dirfd(d), de->d_name, O_DIRECTORY|O_RDONLY);
			if (fd == -1)
				continue;
			dd = fdopendir(fd);
			if (!dd)
				continue;
			f(dd, level + 1);
			closedir(dd);
			break;
		case DT_LNK:
			f_lnk(d, de->d_name);
			break;
		default:
			assert(0);
		}
	}
}