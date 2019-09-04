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
struct csi_priv {int last_eof; int /*<<< orphan*/  sd; int /*<<< orphan*/  last_eof_comp; int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_MEDIA_EOF_TIMEOUT ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi_idmac_wait_last_eof(struct csi_priv *priv)
{
	unsigned long flags;
	int ret;

	/* mark next EOF interrupt as the last before stream off */
	spin_lock_irqsave(&priv->irqlock, flags);
	priv->last_eof = true;
	spin_unlock_irqrestore(&priv->irqlock, flags);

	/*
	 * and then wait for interrupt handler to mark completion.
	 */
	ret = wait_for_completion_timeout(
		&priv->last_eof_comp, msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));
	if (ret == 0)
		v4l2_warn(&priv->sd, "wait last EOF timeout\n");
}