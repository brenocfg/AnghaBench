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
struct vfsmount {int dummy; } ;
struct hlist_head {int dummy; } ;
struct fs_pin {int /*<<< orphan*/  m_list; int /*<<< orphan*/  s_list; } ;
struct TYPE_2__ {struct hlist_head mnt_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  pin_lock ; 
 TYPE_1__* real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pin_insert_group(struct fs_pin *pin, struct vfsmount *m, struct hlist_head *p)
{
	spin_lock(&pin_lock);
	if (p)
		hlist_add_head(&pin->s_list, p);
	hlist_add_head(&pin->m_list, &real_mount(m)->mnt_pins);
	spin_unlock(&pin_lock);
}