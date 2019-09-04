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
typedef  int u16 ;
struct vnt_private {int basic_rates; } ;

/* Variables and functions */
 int RATE_1M ; 

__attribute__((used)) static u16 vnt_get_cck_rate(struct vnt_private *priv, u16 rate_idx)
{
	u16 ui = rate_idx;

	while (ui > RATE_1M) {
		if (priv->basic_rates & (1 << ui))
			return ui;
		ui--;
	}

	return RATE_1M;
}