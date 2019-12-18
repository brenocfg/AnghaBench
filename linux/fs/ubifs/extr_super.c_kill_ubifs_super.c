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
struct ubifs_info {int dummy; } ;
struct super_block {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ubifs_info*) ; 
 int /*<<< orphan*/  kill_anon_super (struct super_block*) ; 

__attribute__((used)) static void kill_ubifs_super(struct super_block *s)
{
	struct ubifs_info *c = s->s_fs_info;
	kill_anon_super(s);
	kfree(c);
}