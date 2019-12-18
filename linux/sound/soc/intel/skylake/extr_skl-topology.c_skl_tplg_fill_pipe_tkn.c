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
struct skl_pipe {int conn_type; int pipe_priority; int memory_pages; int lp_mode; int direction; int nr_cfgs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_TKN_U32_NUM_CONFIGS 133 
#define  SKL_TKN_U32_PIPE_CONN_TYPE 132 
#define  SKL_TKN_U32_PIPE_DIRECTION 131 
#define  SKL_TKN_U32_PIPE_MEM_PGS 130 
#define  SKL_TKN_U32_PIPE_PRIORITY 129 
#define  SKL_TKN_U32_PMODE 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int skl_tplg_fill_pipe_tkn(struct device *dev,
			struct skl_pipe *pipe, u32 tkn,
			u32 tkn_val)
{

	switch (tkn) {
	case SKL_TKN_U32_PIPE_CONN_TYPE:
		pipe->conn_type = tkn_val;
		break;

	case SKL_TKN_U32_PIPE_PRIORITY:
		pipe->pipe_priority = tkn_val;
		break;

	case SKL_TKN_U32_PIPE_MEM_PGS:
		pipe->memory_pages = tkn_val;
		break;

	case SKL_TKN_U32_PMODE:
		pipe->lp_mode = tkn_val;
		break;

	case SKL_TKN_U32_PIPE_DIRECTION:
		pipe->direction = tkn_val;
		break;

	case SKL_TKN_U32_NUM_CONFIGS:
		pipe->nr_cfgs = tkn_val;
		break;

	default:
		dev_err(dev, "Token not handled %d\n", tkn);
		return -EINVAL;
	}

	return 0;
}