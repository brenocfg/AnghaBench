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
typedef  scalar_t__ u32 ;
struct unimac_mdio_priv {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CPU_BIG_ENDIAN ; 
 int /*<<< orphan*/  CONFIG_MIPS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ __raw_readl (scalar_t__) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u32 unimac_mdio_readl(struct unimac_mdio_priv *priv, u32 offset)
{
	/* MIPS chips strapped for BE will automagically configure the
	 * peripheral registers for CPU-native byte order.
	 */
	if (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		return __raw_readl(priv->base + offset);
	else
		return readl_relaxed(priv->base + offset);
}