#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  device_base; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 scalar_t__ PRV_STATE_SLEEP ; 
 int /*<<< orphan*/  isl38xx_trigger_device (int,int /*<<< orphan*/ ) ; 
 scalar_t__ islpci_get_state (TYPE_1__*) ; 

__attribute__((used)) static inline void
islpci_trigger(islpci_private *priv)
{
	isl38xx_trigger_device(islpci_get_state(priv) == PRV_STATE_SLEEP,
			       priv->device_base);
}