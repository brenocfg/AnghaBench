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
struct msm6242_priv {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int msm6242_read(struct msm6242_priv *priv,
				       unsigned int reg)
{
	return __raw_readl(&priv->regs[reg]) & 0xf;
}