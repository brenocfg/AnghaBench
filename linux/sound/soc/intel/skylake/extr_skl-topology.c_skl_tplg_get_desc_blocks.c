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
struct snd_soc_tplg_vendor_value_elem {int token; int value; } ;
struct snd_soc_tplg_vendor_array {struct snd_soc_tplg_vendor_value_elem* value; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_TKN_U16_BLOCK_SIZE 130 
#define  SKL_TKN_U8_BLOCK_TYPE 129 
#define  SKL_TKN_U8_NUM_BLOCKS 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int skl_tplg_get_desc_blocks(struct device *dev,
		struct snd_soc_tplg_vendor_array *array)
{
	struct snd_soc_tplg_vendor_value_elem *tkn_elem;

	tkn_elem = array->value;

	switch (tkn_elem->token) {
	case SKL_TKN_U8_NUM_BLOCKS:
	case SKL_TKN_U8_BLOCK_TYPE:
	case SKL_TKN_U16_BLOCK_SIZE:
		return tkn_elem->value;

	default:
		dev_err(dev, "Invalid descriptor token %d\n", tkn_elem->token);
		break;
	}

	return -EINVAL;
}