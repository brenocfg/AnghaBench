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
struct serial_private {int nr; scalar_t__* line; int /*<<< orphan*/  dev; TYPE_1__* quirk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  serial8250_resume_port (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void pciserial_resume_ports(struct serial_private *priv)
{
	int i;

	/*
	 * Ensure that the board is correctly configured.
	 */
	if (priv->quirk->init)
		priv->quirk->init(priv->dev);

	for (i = 0; i < priv->nr; i++)
		if (priv->line[i] >= 0)
			serial8250_resume_port(priv->line[i]);
}