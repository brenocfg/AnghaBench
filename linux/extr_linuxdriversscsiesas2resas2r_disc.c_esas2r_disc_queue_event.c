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
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_disc_context {int /*<<< orphan*/  disc_evt; } ;
struct esas2r_adapter {int /*<<< orphan*/  flags; struct esas2r_disc_context disc_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CHPRST_PENDING ; 
 int /*<<< orphan*/  AF_DISC_POLLED ; 
 int /*<<< orphan*/  esas2r_disc_start_port (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void esas2r_disc_queue_event(struct esas2r_adapter *a, u8 disc_evt)
{
	struct esas2r_disc_context *dc = &a->disc_ctx;

	esas2r_trace_enter();

	esas2r_trace("disc_event: %d", disc_evt);

	/* Initialize the discovery context */
	dc->disc_evt |= disc_evt;

	/*
	 * Don't start discovery before or during polled discovery.  if we did,
	 * we would have a deadlock if we are in the ISR already.
	 */
	if (!test_bit(AF_CHPRST_PENDING, &a->flags) &&
	    !test_bit(AF_DISC_POLLED, &a->flags))
		esas2r_disc_start_port(a);

	esas2r_trace_exit();
}