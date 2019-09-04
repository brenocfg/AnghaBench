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
struct file_system_type {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 

struct file_system_type *get_filesystem(struct file_system_type *fs)
{
	__module_get(fs->owner);
	return fs;
}