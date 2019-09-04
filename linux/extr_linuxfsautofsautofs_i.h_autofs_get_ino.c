#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct autofs_sb_info {TYPE_1__* sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_root; } ;

/* Variables and functions */
 TYPE_2__* d_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 autofs_get_ino(struct autofs_sb_info *sbi)
{
	return d_inode(sbi->sb->s_root)->i_ino;
}