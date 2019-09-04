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
typedef  int u32 ;
struct sxgbe_priv_data {int /*<<< orphan*/  sxgbe_clk; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 sxgbe_riwt2usec(u32 riwt, struct sxgbe_priv_data *priv)
{
	unsigned long clk = clk_get_rate(priv->sxgbe_clk);

	if (!clk)
		return 0;

	return (riwt * 256) / (clk / 1000000);
}