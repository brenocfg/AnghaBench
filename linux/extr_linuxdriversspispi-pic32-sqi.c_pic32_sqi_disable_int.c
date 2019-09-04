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
struct pic32_sqi {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ PESQI_INT_ENABLE_REG ; 
 scalar_t__ PESQI_INT_SIGEN_REG ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void pic32_sqi_disable_int(struct pic32_sqi *sqi)
{
	writel(0, sqi->regs + PESQI_INT_ENABLE_REG);
	writel(0, sqi->regs + PESQI_INT_SIGEN_REG);
}