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
struct tree_descr {char* member_0; } ;
struct super_block {int /*<<< orphan*/ * s_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAFS_MAGIC ; 
 int /*<<< orphan*/  aafs_super_ops ; 
 int simple_fill_super (struct super_block*,int /*<<< orphan*/ ,struct tree_descr*) ; 

__attribute__((used)) static int fill_super(struct super_block *sb, void *data, int silent)
{
	static struct tree_descr files[] = { {""} };
	int error;

	error = simple_fill_super(sb, AAFS_MAGIC, files);
	if (error)
		return error;
	sb->s_op = &aafs_super_ops;

	return 0;
}