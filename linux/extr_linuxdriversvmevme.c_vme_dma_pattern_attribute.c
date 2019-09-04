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
typedef  void* u32 ;
struct vme_dma_pattern {void* type; void* pattern; } ;
struct vme_dma_attr {void* private; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VME_DMA_PATTERN ; 
 int /*<<< orphan*/  kfree (struct vme_dma_attr*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

struct vme_dma_attr *vme_dma_pattern_attribute(u32 pattern, u32 type)
{
	struct vme_dma_attr *attributes;
	struct vme_dma_pattern *pattern_attr;

	attributes = kmalloc(sizeof(*attributes), GFP_KERNEL);
	if (!attributes)
		goto err_attr;

	pattern_attr = kmalloc(sizeof(*pattern_attr), GFP_KERNEL);
	if (!pattern_attr)
		goto err_pat;

	attributes->type = VME_DMA_PATTERN;
	attributes->private = (void *)pattern_attr;

	pattern_attr->pattern = pattern;
	pattern_attr->type = type;

	return attributes;

err_pat:
	kfree(attributes);
err_attr:
	return NULL;
}