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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_control_lock ; 
 int ocfs2_control_this_node ; 

__attribute__((used)) static int ocfs2_control_get_this_node(void)
{
	int rc;

	mutex_lock(&ocfs2_control_lock);
	if (ocfs2_control_this_node < 0)
		rc = -EINVAL;
	else
		rc = ocfs2_control_this_node;
	mutex_unlock(&ocfs2_control_lock);

	return rc;
}