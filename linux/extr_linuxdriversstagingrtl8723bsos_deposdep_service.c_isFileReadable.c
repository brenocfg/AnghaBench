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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  mm_segment_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  filp_close (struct file*,int /*<<< orphan*/ *) ; 
 struct file* filp_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ds () ; 
 int /*<<< orphan*/  get_fs () ; 
 int readFile (struct file*,char*,int) ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isFileReadable(char *path)
{
	struct file *fp;
	int ret = 0;
	mm_segment_t oldfs;
	char buf;

	fp =filp_open(path, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		ret = PTR_ERR(fp);
	}
	else {
		oldfs = get_fs(); set_fs(get_ds());

		if (1!=readFile(fp, &buf, 1))
			ret = -EINVAL;

		set_fs(oldfs);
		filp_close(fp, NULL);
	}
	return ret;
}