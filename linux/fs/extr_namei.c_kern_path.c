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

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int filename_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getname_kernel (char const*) ; 

int kern_path(const char *name, unsigned int flags, struct path *path)
{
	return filename_lookup(AT_FDCWD, getname_kernel(name),
			       flags, path, NULL);
}