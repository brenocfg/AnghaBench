#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostap_cs_priv {int /*<<< orphan*/ * link; } ;
struct TYPE_3__ {struct hostap_cs_priv* hw_priv; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 scalar_t__ pcmcia_dev_present (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism2_pccard_card_present(local_info_t *local)
{
	struct hostap_cs_priv *hw_priv = local->hw_priv;
	if (hw_priv != NULL && hw_priv->link != NULL && pcmcia_dev_present(hw_priv->link))
		return 1;
	return 0;
}