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

/* Variables and functions */
 int _write_sysfs_int (char const*,char const*,int,int) ; 

int write_sysfs_int_and_verify(const char *filename, const char *basedir,
			       int val)
{
	return _write_sysfs_int(filename, basedir, val, 1);
}