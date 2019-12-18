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
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct fs_pin {int /*<<< orphan*/  m_list; int /*<<< orphan*/  s_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  mnt_pins; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pin_lock ; 
 TYPE_2__* real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pin_insert(struct fs_pin *pin, struct vfsmount *m)
{
	spin_lock(&pin_lock);
	hlist_add_head(&pin->s_list, &m->mnt_sb->s_pins);
	hlist_add_head(&pin->m_list, &real_mount(m)->mnt_pins);
	spin_unlock(&pin_lock);
}