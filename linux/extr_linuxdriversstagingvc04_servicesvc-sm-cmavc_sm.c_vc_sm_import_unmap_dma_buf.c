#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vc_sm_buffer {TYPE_3__* import_dma_buf; } ;
struct sg_table {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* unmap_dma_buf ) (struct dma_buf_attachment*,struct sg_table*,int) ;} ;
struct TYPE_4__ {struct vc_sm_buffer* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dma_buf_attachment*,struct sg_table*,int) ; 

__attribute__((used)) static
void vc_sm_import_unmap_dma_buf(struct dma_buf_attachment *attachment,
				struct sg_table *table,
				enum dma_data_direction direction)
{
	struct vc_sm_buffer *res = attachment->dmabuf->priv;

	if (!res->import_dma_buf)
		return;
	res->import_dma_buf->ops->unmap_dma_buf(attachment, table, direction);
}