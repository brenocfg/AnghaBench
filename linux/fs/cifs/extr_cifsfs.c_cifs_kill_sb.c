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
struct cifs_sb_info {int dummy; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  cifs_umount (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  kill_anon_super (struct super_block*) ; 

__attribute__((used)) static void cifs_kill_sb(struct super_block *sb)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	kill_anon_super(sb);
	cifs_umount(cifs_sb);
}