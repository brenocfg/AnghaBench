#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vbox_private {unsigned int num_crtcs; scalar_t__ available_vram_size; int /*<<< orphan*/ * vbva_info; int /*<<< orphan*/  vbva_buffers; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int VBVA_MIN_BUFFER_SIZE ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iomap_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  vbva_setup_buffer_context (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 

__attribute__((used)) static int vbox_accel_init(struct vbox_private *vbox)
{
	unsigned int i;

	vbox->vbva_info = devm_kcalloc(vbox->dev->dev, vbox->num_crtcs,
				       sizeof(*vbox->vbva_info), GFP_KERNEL);
	if (!vbox->vbva_info)
		return -ENOMEM;

	/* Take a command buffer for each screen from the end of usable VRAM. */
	vbox->available_vram_size -= vbox->num_crtcs * VBVA_MIN_BUFFER_SIZE;

	vbox->vbva_buffers = pci_iomap_range(vbox->dev->pdev, 0,
					     vbox->available_vram_size,
					     vbox->num_crtcs *
					     VBVA_MIN_BUFFER_SIZE);
	if (!vbox->vbva_buffers)
		return -ENOMEM;

	for (i = 0; i < vbox->num_crtcs; ++i)
		vbva_setup_buffer_context(&vbox->vbva_info[i],
					  vbox->available_vram_size +
					  i * VBVA_MIN_BUFFER_SIZE,
					  VBVA_MIN_BUFFER_SIZE);

	return 0;
}