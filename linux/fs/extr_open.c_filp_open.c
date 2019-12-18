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
typedef  int /*<<< orphan*/  umode_t ;
struct filename {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct file* ERR_CAST (struct filename*) ; 
 int /*<<< orphan*/  IS_ERR (struct filename*) ; 
 struct file* file_open_name (struct filename*,int,int /*<<< orphan*/ ) ; 
 struct filename* getname_kernel (char const*) ; 
 int /*<<< orphan*/  putname (struct filename*) ; 

struct file *filp_open(const char *filename, int flags, umode_t mode)
{
	struct filename *name = getname_kernel(filename);
	struct file *file = ERR_CAST(name);
	
	if (!IS_ERR(name)) {
		file = file_open_name(name, flags, mode);
		putname(name);
	}
	return file;
}