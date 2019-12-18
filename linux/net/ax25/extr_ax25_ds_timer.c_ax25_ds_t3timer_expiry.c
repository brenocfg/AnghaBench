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
typedef  int /*<<< orphan*/  ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_COMMAND ; 
 int /*<<< orphan*/  AX25_DISC ; 
 int /*<<< orphan*/  AX25_POLLON ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  ax25_dama_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ax25_disconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_send_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ax25_ds_t3timer_expiry(ax25_cb *ax25)
{
	ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
	ax25_dama_off(ax25);
	ax25_disconnect(ax25, ETIMEDOUT);
}