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
typedef  int u32 ;
struct armada_thermal_priv {TYPE_1__* data; int /*<<< orphan*/  syscon; } ;
struct TYPE_2__ {int is_valid_bit; int /*<<< orphan*/  syscon_status_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_POLL_PERIOD_US ; 
 int /*<<< orphan*/  STATUS_POLL_TIMEOUT_US ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada_wait_sensor_validity(struct armada_thermal_priv *priv)
{
	u32 reg;

	return regmap_read_poll_timeout(priv->syscon,
					priv->data->syscon_status_off, reg,
					reg & priv->data->is_valid_bit,
					STATUS_POLL_PERIOD_US,
					STATUS_POLL_TIMEOUT_US);
}