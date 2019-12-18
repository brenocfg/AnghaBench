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
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __save_error_info (struct super_block*,char const*,unsigned int) ; 
 int /*<<< orphan*/  ext4_commit_super (struct super_block*,int) ; 

__attribute__((used)) static void save_error_info(struct super_block *sb, const char *func,
			    unsigned int line)
{
	__save_error_info(sb, func, line);
	ext4_commit_super(sb, 1);
}