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
struct afs_vnode {unsigned int cb_break; TYPE_1__* volume; } ;
struct afs_cb_interest {int dummy; } ;
struct TYPE_2__ {unsigned int cb_v_break; } ;

/* Variables and functions */

__attribute__((used)) static inline bool afs_cb_is_broken(unsigned int cb_break,
				    const struct afs_vnode *vnode,
				    const struct afs_cb_interest *cbi)
{
	return !cbi || cb_break != (vnode->cb_break +
				    vnode->volume->cb_v_break);
}