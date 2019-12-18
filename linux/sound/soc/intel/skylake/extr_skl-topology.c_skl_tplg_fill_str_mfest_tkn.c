#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_tplg_vendor_string_elem {int token; int /*<<< orphan*/  string; } ;
struct skl_dev {TYPE_1__* lib_info; int /*<<< orphan*/  lib_count; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  SKL_TKN_STR_LIB_NAME 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_tplg_fill_str_mfest_tkn(struct device *dev,
		struct snd_soc_tplg_vendor_string_elem *str_elem,
		struct skl_dev *skl)
{
	int tkn_count = 0;
	static int ref_count;

	switch (str_elem->token) {
	case SKL_TKN_STR_LIB_NAME:
		if (ref_count > skl->lib_count - 1) {
			ref_count = 0;
			return -EINVAL;
		}

		strncpy(skl->lib_info[ref_count].name,
			str_elem->string,
			ARRAY_SIZE(skl->lib_info[ref_count].name));
		ref_count++;
		break;

	default:
		dev_err(dev, "Not a string token %d\n", str_elem->token);
		break;
	}
	tkn_count++;

	return tkn_count;
}