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
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct fs_pin {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  pin_insert_group (struct fs_pin*,struct vfsmount*,int /*<<< orphan*/ *) ; 

void pin_insert(struct fs_pin *pin, struct vfsmount *m)
{
	pin_insert_group(pin, m, &m->mnt_sb->s_pins);
}