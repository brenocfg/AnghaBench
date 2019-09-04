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
typedef  int /*<<< orphan*/  u32 ;
struct dscc4_dev_priv {int /*<<< orphan*/ * scc_regs; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 scc_readl(struct dscc4_dev_priv *dpriv, int offset)
{
	return dpriv->scc_regs[offset >> 2];
}