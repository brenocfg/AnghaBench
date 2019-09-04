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
struct video_frame {int /*<<< orphan*/  y_sgt; int /*<<< orphan*/  y_dmabuf_attachment; int /*<<< orphan*/  cb_sgt; int /*<<< orphan*/  cb_dmabuf_attachment; int /*<<< orphan*/  cr_sgt; int /*<<< orphan*/  cr_dmabuf_attachment; int /*<<< orphan*/  aux_sgt; int /*<<< orphan*/  aux_dmabuf_attachment; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_vde_detach_and_put_dmabuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tegra_vde_release_frame_dmabufs(struct video_frame *frame,
					    enum dma_data_direction dma_dir,
					    bool baseline_profile)
{
	if (!baseline_profile)
		tegra_vde_detach_and_put_dmabuf(frame->aux_dmabuf_attachment,
						frame->aux_sgt, dma_dir);

	tegra_vde_detach_and_put_dmabuf(frame->cr_dmabuf_attachment,
					frame->cr_sgt, dma_dir);

	tegra_vde_detach_and_put_dmabuf(frame->cb_dmabuf_attachment,
					frame->cb_sgt, dma_dir);

	tegra_vde_detach_and_put_dmabuf(frame->y_dmabuf_attachment,
					frame->y_sgt, dma_dir);
}