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
struct grub_dirhook_info {int mtime; scalar_t__ dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char,int,char const*) ; 

int dirhook (const char *filename, const struct grub_dirhook_info *info, void *closure) {
	//info->mtimeset
	//info->case_insensitive
	printf ("DIRFILE: %c (%d) %s\n", info->dir?'d':'f', 
		info->mtime, filename);
	return 0;
}