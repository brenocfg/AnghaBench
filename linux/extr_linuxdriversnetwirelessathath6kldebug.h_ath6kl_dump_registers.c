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
struct ath6kl_irq_proc_registers {int dummy; } ;
struct ath6kl_irq_enable_reg {int dummy; } ;
struct ath6kl_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void ath6kl_dump_registers(struct ath6kl_device *dev,
		struct ath6kl_irq_proc_registers *irq_proc_reg,
		struct ath6kl_irq_enable_reg *irq_en_reg)
{
}