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
typedef  int /*<<< orphan*/  u32 ;
struct gntdev_dmabuf_wait_obj {int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmabuf_exp_wait_obj_wait(struct gntdev_dmabuf_wait_obj *obj,
				    u32 wait_to_ms)
{
	if (wait_for_completion_timeout(&obj->completion,
			msecs_to_jiffies(wait_to_ms)) <= 0)
		return -ETIMEDOUT;

	return 0;
}