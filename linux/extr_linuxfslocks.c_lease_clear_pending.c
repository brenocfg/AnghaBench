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
struct file_lock {int /*<<< orphan*/  fl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_DOWNGRADE_PENDING ; 
 int /*<<< orphan*/  FL_UNLOCK_PENDING ; 
#define  F_RDLCK 129 
#define  F_UNLCK 128 

__attribute__((used)) static void lease_clear_pending(struct file_lock *fl, int arg)
{
	switch (arg) {
	case F_UNLCK:
		fl->fl_flags &= ~FL_UNLOCK_PENDING;
		/* fall through: */
	case F_RDLCK:
		fl->fl_flags &= ~FL_DOWNGRADE_PENDING;
	}
}