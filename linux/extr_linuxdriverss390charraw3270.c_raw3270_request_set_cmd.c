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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_code; } ;
struct raw3270_request {TYPE_1__ ccw; } ;

/* Variables and functions */

void
raw3270_request_set_cmd(struct raw3270_request *rq, u8 cmd)
{
	rq->ccw.cmd_code = cmd;
}