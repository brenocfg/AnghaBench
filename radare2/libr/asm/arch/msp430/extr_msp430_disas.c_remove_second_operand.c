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
 char* strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void remove_second_operand(struct msp430_cmd *cmd)
{
	if (strchr (cmd->operands, ',')) {
		{
			*strchr (cmd->operands, ',') = '\0';
		}
	}
}