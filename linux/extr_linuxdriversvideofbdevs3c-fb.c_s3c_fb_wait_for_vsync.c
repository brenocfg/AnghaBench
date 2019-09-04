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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {unsigned long count; int /*<<< orphan*/  wait; } ;
struct s3c_fb {int /*<<< orphan*/  dev; TYPE_1__ vsync_info; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VSYNC_TIMEOUT_MSEC ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_fb_enable_irq (struct s3c_fb*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c_fb_wait_for_vsync(struct s3c_fb *sfb, u32 crtc)
{
	unsigned long count;
	int ret;

	if (crtc != 0)
		return -ENODEV;

	pm_runtime_get_sync(sfb->dev);

	count = sfb->vsync_info.count;
	s3c_fb_enable_irq(sfb);
	ret = wait_event_interruptible_timeout(sfb->vsync_info.wait,
				       count != sfb->vsync_info.count,
				       msecs_to_jiffies(VSYNC_TIMEOUT_MSEC));

	pm_runtime_put_sync(sfb->dev);

	if (ret == 0)
		return -ETIMEDOUT;

	return 0;
}