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
struct filename {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 struct file* ERR_CAST (struct filename*) ; 
 int /*<<< orphan*/  IS_ERR (struct filename*) ; 
 struct file* do_open_execat (int /*<<< orphan*/ ,struct filename*,int /*<<< orphan*/ ) ; 
 struct filename* getname_kernel (char const*) ; 
 int /*<<< orphan*/  putname (struct filename*) ; 

struct file *open_exec(const char *name)
{
	struct filename *filename = getname_kernel(name);
	struct file *f = ERR_CAST(filename);

	if (!IS_ERR(filename)) {
		f = do_open_execat(AT_FDCWD, filename, 0);
		putname(filename);
	}
	return f;
}