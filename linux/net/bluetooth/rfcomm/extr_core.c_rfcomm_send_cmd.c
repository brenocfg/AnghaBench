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
struct rfcomm_session {int dummy; } ;
struct rfcomm_cmd {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int rfcomm_send_frame (struct rfcomm_session*,void*,int) ; 

__attribute__((used)) static int rfcomm_send_cmd(struct rfcomm_session *s, struct rfcomm_cmd *cmd)
{
	BT_DBG("%p cmd %u", s, cmd->ctrl);

	return rfcomm_send_frame(s, (void *) cmd, sizeof(*cmd));
}