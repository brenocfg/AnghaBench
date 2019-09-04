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
struct il_rx_pkt {int dummy; } ;
struct il_priv {int dummy; } ;
struct TYPE_2__ {scalar_t__ payload; } ;
struct il_device_cmd {TYPE_1__ cmd; } ;
struct il_addsta_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  il_process_add_sta_resp (struct il_priv*,struct il_addsta_cmd*,struct il_rx_pkt*,int) ; 

__attribute__((used)) static void
il_add_sta_callback(struct il_priv *il, struct il_device_cmd *cmd,
		    struct il_rx_pkt *pkt)
{
	struct il_addsta_cmd *addsta = (struct il_addsta_cmd *)cmd->cmd.payload;

	il_process_add_sta_resp(il, addsta, pkt, false);

}