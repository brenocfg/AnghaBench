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
struct prp_priv {int nfb4eof; int /*<<< orphan*/  irqlock; struct imx_ic_priv* ic_priv; } ;
struct imx_ic_priv {int /*<<< orphan*/  sd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static irqreturn_t prp_nfb4eof_interrupt(int irq, void *dev_id)
{
	struct prp_priv *priv = dev_id;
	struct imx_ic_priv *ic_priv = priv->ic_priv;

	spin_lock(&priv->irqlock);

	/*
	 * this is not an unrecoverable error, just mark
	 * the next captured frame with vb2 error flag.
	 */
	priv->nfb4eof = true;

	v4l2_err(&ic_priv->sd, "NFB4EOF\n");

	spin_unlock(&priv->irqlock);

	return IRQ_HANDLED;
}