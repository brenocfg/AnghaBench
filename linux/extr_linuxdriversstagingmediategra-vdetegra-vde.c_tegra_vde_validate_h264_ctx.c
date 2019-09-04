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
struct tegra_vde_h264_decoder_ctx {int dpb_frames_nb; int level_idc; int pic_init_qp; int log2_max_pic_order_cnt_lsb; int log2_max_frame_num; int chroma_qp_index_offset; int pic_order_cnt_type; int num_ref_idx_l0_active_minus1; int num_ref_idx_l1_active_minus1; int pic_width_in_mbs; int pic_height_in_mbs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int tegra_vde_validate_h264_ctx(struct device *dev,
				       struct tegra_vde_h264_decoder_ctx *ctx)
{
	if (ctx->dpb_frames_nb == 0 || ctx->dpb_frames_nb > 17) {
		dev_err(dev, "Bad DPB size %u\n", ctx->dpb_frames_nb);
		return -EINVAL;
	}

	if (ctx->level_idc > 15) {
		dev_err(dev, "Bad level value %u\n", ctx->level_idc);
		return -EINVAL;
	}

	if (ctx->pic_init_qp > 52) {
		dev_err(dev, "Bad pic_init_qp value %u\n", ctx->pic_init_qp);
		return -EINVAL;
	}

	if (ctx->log2_max_pic_order_cnt_lsb > 16) {
		dev_err(dev, "Bad log2_max_pic_order_cnt_lsb value %u\n",
			ctx->log2_max_pic_order_cnt_lsb);
		return -EINVAL;
	}

	if (ctx->log2_max_frame_num > 16) {
		dev_err(dev, "Bad log2_max_frame_num value %u\n",
			ctx->log2_max_frame_num);
		return -EINVAL;
	}

	if (ctx->chroma_qp_index_offset > 31) {
		dev_err(dev, "Bad chroma_qp_index_offset value %u\n",
			ctx->chroma_qp_index_offset);
		return -EINVAL;
	}

	if (ctx->pic_order_cnt_type > 2) {
		dev_err(dev, "Bad pic_order_cnt_type value %u\n",
			ctx->pic_order_cnt_type);
		return -EINVAL;
	}

	if (ctx->num_ref_idx_l0_active_minus1 > 15) {
		dev_err(dev, "Bad num_ref_idx_l0_active_minus1 value %u\n",
			ctx->num_ref_idx_l0_active_minus1);
		return -EINVAL;
	}

	if (ctx->num_ref_idx_l1_active_minus1 > 15) {
		dev_err(dev, "Bad num_ref_idx_l1_active_minus1 value %u\n",
			ctx->num_ref_idx_l1_active_minus1);
		return -EINVAL;
	}

	if (!ctx->pic_width_in_mbs || ctx->pic_width_in_mbs > 127) {
		dev_err(dev, "Bad pic_width_in_mbs value %u\n",
			ctx->pic_width_in_mbs);
		return -EINVAL;
	}

	if (!ctx->pic_height_in_mbs || ctx->pic_height_in_mbs > 127) {
		dev_err(dev, "Bad pic_height_in_mbs value %u\n",
			ctx->pic_height_in_mbs);
		return -EINVAL;
	}

	return 0;
}