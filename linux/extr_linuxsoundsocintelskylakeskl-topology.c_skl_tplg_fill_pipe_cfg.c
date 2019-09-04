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
typedef  int u32 ;
struct skl_pipe_fmt {int freq; int channels; int bps; } ;
struct skl_pipe {struct skl_path_config* configs; } ;
struct skl_path_config {int mem_pages; struct skl_pipe_fmt out_fmt; struct skl_pipe_fmt in_fmt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_DIR_IN 133 
#define  SKL_DIR_OUT 132 
#define  SKL_TKN_U32_CFG_FREQ 131 
#define  SKL_TKN_U32_PATH_MEM_PGS 130 
#define  SKL_TKN_U8_CFG_BPS 129 
#define  SKL_TKN_U8_CFG_CHAN 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int skl_tplg_fill_pipe_cfg(struct device *dev,
			struct skl_pipe *pipe, u32 tkn,
			u32 tkn_val, int conf_idx, int dir)
{
	struct skl_pipe_fmt *fmt;
	struct skl_path_config *config;

	switch (dir) {
	case SKL_DIR_IN:
		fmt = &pipe->configs[conf_idx].in_fmt;
		break;

	case SKL_DIR_OUT:
		fmt = &pipe->configs[conf_idx].out_fmt;
		break;

	default:
		dev_err(dev, "Invalid direction: %d\n", dir);
		return -EINVAL;
	}

	config = &pipe->configs[conf_idx];

	switch (tkn) {
	case SKL_TKN_U32_CFG_FREQ:
		fmt->freq = tkn_val;
		break;

	case SKL_TKN_U8_CFG_CHAN:
		fmt->channels = tkn_val;
		break;

	case SKL_TKN_U8_CFG_BPS:
		fmt->bps = tkn_val;
		break;

	case SKL_TKN_U32_PATH_MEM_PGS:
		config->mem_pages = tkn_val;
		break;

	default:
		dev_err(dev, "Invalid token config: %d\n", tkn);
		return -EINVAL;
	}

	return 0;
}