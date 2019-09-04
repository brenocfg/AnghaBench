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
struct the_nilfs {int dummy; } ;
struct nilfs_superblock_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 char* sb_readme_str ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
nilfs_superblock_README_show(struct nilfs_superblock_attr *attr,
				struct the_nilfs *nilfs, char *buf)
{
	return snprintf(buf, PAGE_SIZE, sb_readme_str);
}