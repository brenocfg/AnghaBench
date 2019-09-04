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
struct il_rxon_cmd {int /*<<< orphan*/  filter_flags; } ;
struct il_priv {struct il_rxon_cmd staging; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXON_FILTER_DIS_DECRYPT_MSK ; 

void
il_set_rxon_hwcrypto(struct il_priv *il, int hw_decrypt)
{
	struct il_rxon_cmd *rxon = &il->staging;

	if (hw_decrypt)
		rxon->filter_flags &= ~RXON_FILTER_DIS_DECRYPT_MSK;
	else
		rxon->filter_flags |= RXON_FILTER_DIS_DECRYPT_MSK;

}