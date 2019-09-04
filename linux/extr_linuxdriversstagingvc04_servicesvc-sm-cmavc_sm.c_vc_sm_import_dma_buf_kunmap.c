#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc_sm_buffer {TYPE_2__* import_dma_buf; } ;
struct dma_buf {struct vc_sm_buffer* priv; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unmap ) (TYPE_2__*,unsigned long,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned long,void*) ; 

__attribute__((used)) static
void vc_sm_import_dma_buf_kunmap(struct dma_buf *dmabuf,
				 unsigned long offset, void *ptr)
{
	struct vc_sm_buffer *res = dmabuf->priv;

	if (!res->import_dma_buf)
		return;
	res->import_dma_buf->ops->unmap(res->import_dma_buf,
					       offset, ptr);
}