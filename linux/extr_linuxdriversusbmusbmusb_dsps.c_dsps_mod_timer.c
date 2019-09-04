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
struct musb {int /*<<< orphan*/  dev_timer; } ;
struct dsps_glue {TYPE_1__* wrp; int /*<<< orphan*/  musb; } ;
struct TYPE_2__ {int poll_timeout; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int msecs_to_jiffies (int) ; 
 struct musb* platform_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsps_mod_timer(struct dsps_glue *glue, int wait_ms)
{
	struct musb *musb = platform_get_drvdata(glue->musb);
	int wait;

	if (wait_ms < 0)
		wait = msecs_to_jiffies(glue->wrp->poll_timeout);
	else
		wait = msecs_to_jiffies(wait_ms);

	mod_timer(&musb->dev_timer, jiffies + wait);
}