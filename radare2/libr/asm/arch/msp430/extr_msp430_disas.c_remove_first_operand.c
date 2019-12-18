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
struct msp430_cmd {int /*<<< orphan*/  operands; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static void remove_first_operand(struct msp430_cmd *cmd)
{
	if (strchr(cmd->operands, ',')) {
		memmove(cmd->operands, strchr(cmd->operands, ',') + 2,
				strlen(strchr(cmd->operands, ',') + 2) + 1);
	}
}