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
struct ocfs2_control_private {int op_state; } ;
struct file {struct ocfs2_control_private* private_data; } ;

/* Variables and functions */

__attribute__((used)) static inline void ocfs2_control_set_handshake_state(struct file *file,
						     int state)
{
	struct ocfs2_control_private *p = file->private_data;
	p->op_state = state;
}