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
struct vgic_irq {void* owner; int config; int line_level; } ;

/* Variables and functions */
#define  VGIC_CONFIG_EDGE 129 
#define  VGIC_CONFIG_LEVEL 128 

__attribute__((used)) static bool vgic_validate_injection(struct vgic_irq *irq, bool level, void *owner)
{
	if (irq->owner != owner)
		return false;

	switch (irq->config) {
	case VGIC_CONFIG_LEVEL:
		return irq->line_level != level;
	case VGIC_CONFIG_EDGE:
		return level;
	}

	return false;
}