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
struct afs_vnode {unsigned int cb_break; TYPE_2__* volume; } ;
struct afs_cb_interest {TYPE_1__* server; } ;
struct TYPE_4__ {unsigned int cb_v_break; } ;
struct TYPE_3__ {unsigned int cb_s_break; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int afs_cb_break_sum(struct afs_vnode *vnode,
					    struct afs_cb_interest *cbi)
{
	return vnode->cb_break + cbi->server->cb_s_break + vnode->volume->cb_v_break;
}