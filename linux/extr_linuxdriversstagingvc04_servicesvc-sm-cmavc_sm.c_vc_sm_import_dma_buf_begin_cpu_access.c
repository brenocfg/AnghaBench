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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* begin_cpu_access ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static
int vc_sm_import_dma_buf_begin_cpu_access(struct dma_buf *dmabuf,
					  enum dma_data_direction direction)
{
	struct vc_sm_buffer *res = dmabuf->priv;

	if (!res->import_dma_buf)
		return -EINVAL;
	return res->import_dma_buf->ops->begin_cpu_access(res->import_dma_buf,
							    direction);
}