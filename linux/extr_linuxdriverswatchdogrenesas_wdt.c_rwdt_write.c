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
typedef  int u32 ;
struct rwdt_priv {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int RWTCNT ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void rwdt_write(struct rwdt_priv *priv, u32 val, unsigned int reg)
{
	if (reg == RWTCNT)
		val |= 0x5a5a0000;
	else
		val |= 0xa5a5a500;

	writel_relaxed(val, priv->base + reg);
}