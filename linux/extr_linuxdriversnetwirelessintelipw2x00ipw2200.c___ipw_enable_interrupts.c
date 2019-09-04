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
struct ipw_priv {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_INTA_MASK_ALL ; 
 int /*<<< orphan*/  IPW_INTA_MASK_R ; 
 int STATUS_INT_ENABLED ; 
 int /*<<< orphan*/  ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __ipw_enable_interrupts(struct ipw_priv *priv)
{
	if (priv->status & STATUS_INT_ENABLED)
		return;
	priv->status |= STATUS_INT_ENABLED;
	ipw_write32(priv, IPW_INTA_MASK_R, IPW_INTA_MASK_ALL);
}