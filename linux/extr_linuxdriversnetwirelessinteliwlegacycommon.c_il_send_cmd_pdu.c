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
struct il_host_cmd {void const* data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int il_send_cmd_sync (struct il_priv*,struct il_host_cmd*) ; 

int
il_send_cmd_pdu(struct il_priv *il, u8 id, u16 len, const void *data)
{
	struct il_host_cmd cmd = {
		.id = id,
		.len = len,
		.data = data,
	};

	return il_send_cmd_sync(il, &cmd);
}