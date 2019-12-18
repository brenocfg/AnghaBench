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
struct dirent {scalar_t__ d_type; } ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int lsdir_no_dot_filter (char const*,struct dirent*) ; 

__attribute__((used)) static bool visible_dir_filter(const char *name, struct dirent *d)
{
	if (d->d_type != DT_DIR)
		return false;
	return lsdir_no_dot_filter(name, d);
}