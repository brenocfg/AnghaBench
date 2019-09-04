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
struct super_block {void* s_fs_info; } ;

/* Variables and functions */
 int set_anon_super (struct super_block*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ns_set_super(struct super_block *sb, void *data)
{
	sb->s_fs_info = data;
	return set_anon_super(sb, NULL);
}