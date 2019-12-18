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
struct snd_soc_tplg_vendor_value_elem {int token; int /*<<< orphan*/  value; } ;
struct skl_module_res {int /*<<< orphan*/  ibs; int /*<<< orphan*/  obs; int /*<<< orphan*/  is_pages; int /*<<< orphan*/  cpc; int /*<<< orphan*/  dma_buffer_size; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_TKN_MM_U32_CPC 136 
#define  SKL_TKN_MM_U32_CPS 135 
#define  SKL_TKN_MM_U32_DMA_SIZE 134 
#define  SKL_TKN_MM_U32_PIN_BUF 133 
#define  SKL_TKN_MM_U32_RES_PIN_ID 132 
#define  SKL_TKN_U32_IBS 131 
#define  SKL_TKN_U32_MAX_MCPS 130 
#define  SKL_TKN_U32_MEM_PAGES 129 
#define  SKL_TKN_U32_OBS 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int skl_tplg_manifest_pin_res_tkn (struct device*,struct snd_soc_tplg_vendor_value_elem*,struct skl_module_res*,int,int) ; 

__attribute__((used)) static int skl_tplg_fill_res_tkn(struct device *dev,
		struct snd_soc_tplg_vendor_value_elem *tkn_elem,
		struct skl_module_res *res,
		int pin_idx, int dir)
{
	int ret, tkn_count = 0;

	if (!res)
		return -EINVAL;

	switch (tkn_elem->token) {
	case SKL_TKN_MM_U32_DMA_SIZE:
		res->dma_buffer_size = tkn_elem->value;
		break;

	case SKL_TKN_MM_U32_CPC:
		res->cpc = tkn_elem->value;
		break;

	case SKL_TKN_U32_MEM_PAGES:
		res->is_pages = tkn_elem->value;
		break;

	case SKL_TKN_U32_OBS:
		res->obs = tkn_elem->value;
		break;

	case SKL_TKN_U32_IBS:
		res->ibs = tkn_elem->value;
		break;

	case SKL_TKN_MM_U32_RES_PIN_ID:
	case SKL_TKN_MM_U32_PIN_BUF:
		ret = skl_tplg_manifest_pin_res_tkn(dev, tkn_elem, res,
						    pin_idx, dir);
		if (ret < 0)
			return ret;
		break;

	case SKL_TKN_MM_U32_CPS:
	case SKL_TKN_U32_MAX_MCPS:
		/* ignore unused tokens */
		break;

	default:
		dev_err(dev, "Not a res type token: %d", tkn_elem->token);
		return -EINVAL;

	}
	tkn_count++;

	return tkn_count;
}