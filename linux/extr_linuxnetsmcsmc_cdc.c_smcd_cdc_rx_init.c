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
struct smc_connection {int /*<<< orphan*/  rx_tsklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  smcd_cdc_rx_tsklet ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void smcd_cdc_rx_init(struct smc_connection *conn)
{
	tasklet_init(&conn->rx_tsklet, smcd_cdc_rx_tsklet, (unsigned long)conn);
}