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
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_state {int dummy; } ;
struct TYPE_2__ {int hard; } ;
struct km_event {int /*<<< orphan*/  event; int /*<<< orphan*/  portid; TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_MSG_EXPIRE ; 
 int /*<<< orphan*/  km_state_notify (struct xfrm_state*,struct km_event*) ; 

void km_state_expired(struct xfrm_state *x, int hard, u32 portid)
{
	struct km_event c;

	c.data.hard = hard;
	c.portid = portid;
	c.event = XFRM_MSG_EXPIRE;
	km_state_notify(x, &c);
}