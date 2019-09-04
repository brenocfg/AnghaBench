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
struct mipid_device {int dummy; } ;

/* Variables and functions */
 int MIPID_CMD_DISP_OFF ; 
 int MIPID_CMD_DISP_ON ; 
 int /*<<< orphan*/  mipid_cmd (struct mipid_device*,int) ; 

__attribute__((used)) static void set_display_state(struct mipid_device *md, int enabled)
{
	int cmd = enabled ? MIPID_CMD_DISP_ON : MIPID_CMD_DISP_OFF;

	mipid_cmd(md, cmd);
}