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
struct super_block {int /*<<< orphan*/  s_active; } ;
struct cifs_sb_info {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

void
cifs_sb_active(struct super_block *sb)
{
	struct cifs_sb_info *server = CIFS_SB(sb);

	if (atomic_inc_return(&server->active) == 1)
		atomic_inc(&sb->s_active);
}