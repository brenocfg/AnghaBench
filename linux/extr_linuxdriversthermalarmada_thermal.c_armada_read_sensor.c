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
typedef  int s64 ;
struct TYPE_2__ {int temp_shift; int temp_mask; int coef_b; int coef_m; int coef_div; scalar_t__ inverted; scalar_t__ signed_sample; int /*<<< orphan*/  syscon_status_off; } ;

/* Variables and functions */
 int div_s64 (int,int) ; 
 scalar_t__ fls (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sign_extend32 (int,scalar_t__) ; 

__attribute__((used)) static int armada_read_sensor(struct armada_thermal_priv *priv, int *temp)
{
	u32 reg, div;
	s64 sample, b, m;

	regmap_read(priv->syscon, priv->data->syscon_status_off, &reg);
	reg = (reg >> priv->data->temp_shift) & priv->data->temp_mask;
	if (priv->data->signed_sample)
		/* The most significant bit is the sign bit */
		sample = sign_extend32(reg, fls(priv->data->temp_mask) - 1);
	else
		sample = reg;

	/* Get formula coeficients */
	b = priv->data->coef_b;
	m = priv->data->coef_m;
	div = priv->data->coef_div;

	if (priv->data->inverted)
		*temp = div_s64((m * sample) - b, div);
	else
		*temp = div_s64(b - (m * sample), div);

	return 0;
}