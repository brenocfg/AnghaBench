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
struct super_block {int /*<<< orphan*/  s_fs_info; } ;
struct cifs_mnt_data {int /*<<< orphan*/  cifs_sb; } ;

/* Variables and functions */
 int set_anon_super (struct super_block*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cifs_set_super(struct super_block *sb, void *data)
{
	struct cifs_mnt_data *mnt_data = data;
	sb->s_fs_info = mnt_data->cifs_sb;
	return set_anon_super(sb, NULL);
}