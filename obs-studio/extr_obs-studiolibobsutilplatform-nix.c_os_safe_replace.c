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
 scalar_t__ os_file_exists (char const*) ; 
 int rename (char const*,char const*) ; 

int os_safe_replace(const char *target, const char *from, const char *backup)
{
	if (backup && os_file_exists(target) && rename(target, backup) != 0)
		return -1;
	return rename(from, target);
}