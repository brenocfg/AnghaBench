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
struct TYPE_2__ {int /*<<< orphan*/  procdir; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  proc_create_single_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (struct seq_file*,void*),struct super_block*) ; 

__attribute__((used)) static void add_file(struct super_block *sb, char *name,
		     int (*func) (struct seq_file *, void *))
{
	proc_create_single_data(name, 0, REISERFS_SB(sb)->procdir, func, sb);
}