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
struct atmel_pwm_chip {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u32 atmel_pwm_readl(struct atmel_pwm_chip *chip,
				  unsigned long offset)
{
	return readl_relaxed(chip->base + offset);
}