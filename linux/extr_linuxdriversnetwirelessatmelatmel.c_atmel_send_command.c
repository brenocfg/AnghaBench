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
struct atmel_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_BLOCK_COMMAND_OFFSET ; 
 int /*<<< orphan*/  CMD_BLOCK_PARAMETERS_OFFSET ; 
 int /*<<< orphan*/  CMD_BLOCK_STATUS_OFFSET ; 
 int /*<<< orphan*/  atmel_co (struct atmel_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_copy_to_card (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  atmel_wmem8 (struct atmel_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atmel_send_command(struct atmel_private *priv, int command,
			       void *cmd, int cmd_size)
{
	if (cmd)
		atmel_copy_to_card(priv->dev, atmel_co(priv, CMD_BLOCK_PARAMETERS_OFFSET),
				   cmd, cmd_size);

	atmel_wmem8(priv, atmel_co(priv, CMD_BLOCK_COMMAND_OFFSET), command);
	atmel_wmem8(priv, atmel_co(priv, CMD_BLOCK_STATUS_OFFSET), 0);
}