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
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct audit_fsnotify_mark {int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_DEV_UNSET ; 
 int /*<<< orphan*/  AUDIT_INO_UNSET ; 

__attribute__((used)) static void audit_update_mark(struct audit_fsnotify_mark *audit_mark,
			     const struct inode *inode)
{
	audit_mark->dev = inode ? inode->i_sb->s_dev : AUDIT_DEV_UNSET;
	audit_mark->ino = inode ? inode->i_ino : AUDIT_INO_UNSET;
}