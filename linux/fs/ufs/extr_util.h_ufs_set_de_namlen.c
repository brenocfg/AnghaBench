#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  d_namlen; } ;
struct TYPE_5__ {TYPE_1__ d_44; int /*<<< orphan*/  d_namlen; } ;
struct ufs_dir_entry {TYPE_2__ d_u; } ;
struct super_block {int dummy; } ;
struct TYPE_6__ {int s_flags; } ;

/* Variables and functions */
 int UFS_DE_MASK ; 
 int UFS_DE_OLD ; 
 TYPE_3__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  cpu_to_fs16 (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ufs_set_de_namlen(struct super_block *sb, struct ufs_dir_entry *de, u16 value)
{
	if ((UFS_SB(sb)->s_flags & UFS_DE_MASK) == UFS_DE_OLD)
		de->d_u.d_namlen = cpu_to_fs16(sb, value);
	else
		de->d_u.d_44.d_namlen = value; /* XXX this seems wrong */
}