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
struct virt_dma_desc {int dummy; } ;
struct gdma_dmaengine_chan {scalar_t__ next_sg; int /*<<< orphan*/ * desc; int /*<<< orphan*/  vchan; } ;

/* Variables and functions */
 int /*<<< orphan*/ * to_gdma_dma_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gdma_next_desc(struct gdma_dmaengine_chan *chan)
{
	struct virt_dma_desc *vdesc;

	vdesc = vchan_next_desc(&chan->vchan);
	if (!vdesc) {
		chan->desc = NULL;
		return 0;
	}
	chan->desc = to_gdma_dma_desc(vdesc);
	chan->next_sg = 0;

	return 1;
}