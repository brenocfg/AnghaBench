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
struct il_priv {int dummy; } ;
struct il_led_cmd {int dummy; } ;
struct il_host_cmd {int len; int /*<<< orphan*/ * callback; int /*<<< orphan*/  flags; struct il_led_cmd* data; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  C_LEDS ; 
 int il_send_cmd (struct il_priv*,struct il_host_cmd*) ; 

__attribute__((used)) static int
il3945_send_led_cmd(struct il_priv *il, struct il_led_cmd *led_cmd)
{
	struct il_host_cmd cmd = {
		.id = C_LEDS,
		.len = sizeof(struct il_led_cmd),
		.data = led_cmd,
		.flags = CMD_ASYNC,
		.callback = NULL,
	};

	return il_send_cmd(il, &cmd);
}