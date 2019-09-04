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
struct lapb_cb {int condition; int mode; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; scalar_t__ n2count; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAPB_COMMAND ; 
 int LAPB_EXTENDED ; 
 int /*<<< orphan*/  LAPB_POLLON ; 
 int /*<<< orphan*/  LAPB_SABM ; 
 int /*<<< orphan*/  LAPB_SABME ; 
 int /*<<< orphan*/  lapb_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_send_control (struct lapb_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_start_t1timer (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_stop_t2timer (struct lapb_cb*) ; 

void lapb_establish_data_link(struct lapb_cb *lapb)
{
	lapb->condition = 0x00;
	lapb->n2count   = 0;

	if (lapb->mode & LAPB_EXTENDED) {
		lapb_dbg(1, "(%p) S%d TX SABME(1)\n", lapb->dev, lapb->state);
		lapb_send_control(lapb, LAPB_SABME, LAPB_POLLON, LAPB_COMMAND);
	} else {
		lapb_dbg(1, "(%p) S%d TX SABM(1)\n", lapb->dev, lapb->state);
		lapb_send_control(lapb, LAPB_SABM, LAPB_POLLON, LAPB_COMMAND);
	}

	lapb_start_t1timer(lapb);
	lapb_stop_t2timer(lapb);
}