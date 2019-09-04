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
struct rp5c01_priv {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int rp5c01_read(struct rp5c01_priv *priv,
				       unsigned int reg)
{
	return __raw_readl(&priv->regs[reg]) & 0xf;
}