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
struct rk3328_codec_priv {int /*<<< orphan*/  grf; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  RK3328_GRF_SOC_CON10 ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void rk3328_analog_output(struct rk3328_codec_priv *rk3328, int mute)
{
	unsigned int val = BIT(17);

	if (mute)
		val |= BIT(1);

	regmap_write(rk3328->grf, RK3328_GRF_SOC_CON10, val);
}