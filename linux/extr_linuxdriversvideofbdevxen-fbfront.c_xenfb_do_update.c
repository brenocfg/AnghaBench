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
struct TYPE_2__ {int x; int y; int width; int height; } ;
union xenfb_out_event {TYPE_1__ update; int /*<<< orphan*/  type; } ;
struct xenfb_info {int dummy; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  XENFB_TYPE_UPDATE ; 
 int /*<<< orphan*/  memset (union xenfb_out_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xenfb_send_event (struct xenfb_info*,union xenfb_out_event*) ; 

__attribute__((used)) static void xenfb_do_update(struct xenfb_info *info,
			    int x, int y, int w, int h)
{
	union xenfb_out_event event;

	memset(&event, 0, sizeof(event));
	event.type = XENFB_TYPE_UPDATE;
	event.update.x = x;
	event.update.y = y;
	event.update.width = w;
	event.update.height = h;

	/* caller ensures !xenfb_queue_full() */
	xenfb_send_event(info, &event);
}