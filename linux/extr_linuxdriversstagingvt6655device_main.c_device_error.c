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
struct vnt_private {TYPE_1__* pcid; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short ISR_FETALERR ; 
 int /*<<< orphan*/  MACbShutdown (struct vnt_private*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void device_error(struct vnt_private *priv, unsigned short status)
{
	if (status & ISR_FETALERR) {
		dev_err(&priv->pcid->dev, "Hardware fatal error\n");

		MACbShutdown(priv);
		return;
	}
}