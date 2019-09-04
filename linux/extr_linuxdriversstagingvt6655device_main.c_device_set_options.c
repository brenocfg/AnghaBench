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
struct TYPE_2__ {scalar_t__ bbp_type; scalar_t__ long_retry; scalar_t__ short_retry; } ;
struct vnt_private {int bUpdateBBVGA; scalar_t__ byBBType; scalar_t__ byShortPreamble; scalar_t__ byPreambleType; scalar_t__ byLongRetryLimit; scalar_t__ byShortRetryLimit; int /*<<< orphan*/  byAutoFBCtrl; scalar_t__ byPacketType; TYPE_1__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_FB_0 ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static void
device_set_options(struct vnt_private *priv)
{
	priv->byShortRetryLimit = priv->opts.short_retry;
	priv->byLongRetryLimit = priv->opts.long_retry;
	priv->byBBType = priv->opts.bbp_type;
	priv->byPacketType = priv->byBBType;
	priv->byAutoFBCtrl = AUTO_FB_0;
	priv->bUpdateBBVGA = true;
	priv->byPreambleType = 0;

	pr_debug(" byShortRetryLimit= %d\n", (int)priv->byShortRetryLimit);
	pr_debug(" byLongRetryLimit= %d\n", (int)priv->byLongRetryLimit);
	pr_debug(" byPreambleType= %d\n", (int)priv->byPreambleType);
	pr_debug(" byShortPreamble= %d\n", (int)priv->byShortPreamble);
	pr_debug(" byBBType= %d\n", (int)priv->byBBType);
}