#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nlm_file {int /*<<< orphan*/  f_file; } ;
struct TYPE_2__ {struct super_block* i_sb; } ;

/* Variables and functions */
 TYPE_1__* locks_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nlmsvc_match_sb(void *datap, struct nlm_file *file)
{
	struct super_block *sb = datap;

	return sb == locks_inode(file->f_file)->i_sb;
}