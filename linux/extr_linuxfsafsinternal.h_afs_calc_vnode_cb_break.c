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
struct afs_vnode {unsigned int cb_break; unsigned int cb_s_break; unsigned int cb_v_break; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int afs_calc_vnode_cb_break(struct afs_vnode *vnode)
{
	return vnode->cb_break + vnode->cb_s_break + vnode->cb_v_break;
}