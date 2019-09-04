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
struct ks_wlan_private {int /*<<< orphan*/  sme_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void hostif_exit(struct ks_wlan_private *priv)
{
	tasklet_kill(&priv->sme_task);
}