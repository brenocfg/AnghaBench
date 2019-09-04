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
struct ks_wlan_private {int current_rate; int /*<<< orphan*/  connect_status; scalar_t__ infra_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCONNECT_STATUS ; 

__attribute__((used)) static inline void hostif_status_init(struct ks_wlan_private *priv)
{
	priv->infra_status = 0;
	priv->current_rate = 4;
	priv->connect_status = DISCONNECT_STATUS;
}