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
struct tool_ctx {int /*<<< orphan*/  link_wq; TYPE_1__* ntb; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,int,int) ; 
 int ntb_link_is_up (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tool_link_event(void *ctx)
{
	struct tool_ctx *tc = ctx;
	enum ntb_speed speed;
	enum ntb_width width;
	int up;

	up = ntb_link_is_up(tc->ntb, &speed, &width);

	dev_dbg(&tc->ntb->dev, "link is %s speed %d width %d\n",
		up ? "up" : "down", speed, width);

	wake_up(&tc->link_wq);
}