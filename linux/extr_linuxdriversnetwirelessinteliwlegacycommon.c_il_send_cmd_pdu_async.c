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
typedef  int /*<<< orphan*/  u16 ;
struct il_priv {int dummy; } ;
struct il_host_cmd {void const* data; void (* callback ) (struct il_priv*,struct il_device_cmd*,struct il_rx_pkt*) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int il_send_cmd_async (struct il_priv*,struct il_host_cmd*) ; 

int
il_send_cmd_pdu_async(struct il_priv *il, u8 id, u16 len, const void *data,
		      void (*callback) (struct il_priv *il,
					struct il_device_cmd *cmd,
					struct il_rx_pkt *pkt))
{
	struct il_host_cmd cmd = {
		.id = id,
		.len = len,
		.data = data,
	};

	cmd.flags |= CMD_ASYNC;
	cmd.callback = callback;

	return il_send_cmd_async(il, &cmd);
}