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
struct lx_stream {int status; } ;
struct lx6464es {int dummy; } ;

/* Variables and functions */
#define  LX_STREAM_STATUS_SCHEDULE_RUN 129 
#define  LX_STREAM_STATUS_SCHEDULE_STOP 128 
 int /*<<< orphan*/  lx_trigger_start (struct lx6464es*,struct lx_stream*) ; 
 int /*<<< orphan*/  lx_trigger_stop (struct lx6464es*,struct lx_stream*) ; 

__attribute__((used)) static void lx_trigger_dispatch_stream(struct lx6464es *chip,
				       struct lx_stream *lx_stream)
{
	switch (lx_stream->status) {
	case LX_STREAM_STATUS_SCHEDULE_RUN:
		lx_trigger_start(chip, lx_stream);
		break;

	case LX_STREAM_STATUS_SCHEDULE_STOP:
		lx_trigger_stop(chip, lx_stream);
		break;

	default:
		break;
	}
}