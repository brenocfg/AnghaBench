#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pn533 {TYPE_2__* cmd; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct TYPE_3__ {scalar_t__ (* get_cmd_code ) (void*) ;} ;

/* Variables and functions */
 scalar_t__ PN533_CMD_RESPONSE (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (void*) ; 

bool pn533_rx_frame_is_cmd_response(struct pn533 *dev, void *frame)
{
	return (dev->ops->get_cmd_code(frame) ==
				PN533_CMD_RESPONSE(dev->cmd->code));
}