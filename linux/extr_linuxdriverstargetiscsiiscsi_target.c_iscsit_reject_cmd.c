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
struct iscsi_cmd {int dummy; } ;

/* Variables and functions */
 int iscsit_add_reject_from_cmd (struct iscsi_cmd*,int /*<<< orphan*/ ,int,unsigned char*) ; 

int iscsit_reject_cmd(struct iscsi_cmd *cmd, u8 reason, unsigned char *buf)
{
	return iscsit_add_reject_from_cmd(cmd, reason, false, buf);
}