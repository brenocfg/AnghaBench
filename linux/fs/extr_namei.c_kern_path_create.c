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
struct path {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* filename_create (int,int /*<<< orphan*/ ,struct path*,unsigned int) ; 
 int /*<<< orphan*/  getname_kernel (char const*) ; 

struct dentry *kern_path_create(int dfd, const char *pathname,
				struct path *path, unsigned int lookup_flags)
{
	return filename_create(dfd, getname_kernel(pathname),
				path, lookup_flags);
}