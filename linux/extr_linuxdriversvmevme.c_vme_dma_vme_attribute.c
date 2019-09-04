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
struct vme_dma_vme {unsigned long long address; void* dwidth; void* cycle; void* aspace; } ;
struct vme_dma_attr {void* private; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VME_DMA_VME ; 
 int /*<<< orphan*/  kfree (struct vme_dma_attr*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

struct vme_dma_attr *vme_dma_vme_attribute(unsigned long long address,
	u32 aspace, u32 cycle, u32 dwidth)
{
	struct vme_dma_attr *attributes;
	struct vme_dma_vme *vme_attr;

	attributes = kmalloc(sizeof(*attributes), GFP_KERNEL);
	if (!attributes)
		goto err_attr;

	vme_attr = kmalloc(sizeof(*vme_attr), GFP_KERNEL);
	if (!vme_attr)
		goto err_vme;

	attributes->type = VME_DMA_VME;
	attributes->private = (void *)vme_attr;

	vme_attr->address = address;
	vme_attr->aspace = aspace;
	vme_attr->cycle = cycle;
	vme_attr->dwidth = dwidth;

	return attributes;

err_vme:
	kfree(attributes);
err_attr:
	return NULL;
}