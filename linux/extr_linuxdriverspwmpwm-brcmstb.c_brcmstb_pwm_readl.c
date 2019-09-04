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
struct brcmstb_pwm {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CPU_BIG_ENDIAN ; 
 int /*<<< orphan*/  CONFIG_MIPS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u32 brcmstb_pwm_readl(struct brcmstb_pwm *p,
				    unsigned int offset)
{
	if (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		return __raw_readl(p->base + offset);
	else
		return readl_relaxed(p->base + offset);
}