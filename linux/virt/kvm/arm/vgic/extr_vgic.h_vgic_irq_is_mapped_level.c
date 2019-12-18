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
struct vgic_irq {scalar_t__ config; scalar_t__ hw; } ;

/* Variables and functions */
 scalar_t__ VGIC_CONFIG_LEVEL ; 

__attribute__((used)) static inline bool vgic_irq_is_mapped_level(struct vgic_irq *irq)
{
	return irq->config == VGIC_CONFIG_LEVEL && irq->hw;
}