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
typedef  int u32 ;
struct iwl_trans {int dummy; } ;
struct fw_img {int num_sec; TYPE_1__* sec; } ;
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ CPU1_CPU2_SEPARATOR_SECTION ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_trans*,char*,int) ; 
 scalar_t__ PAGING_SEPARATOR_SECTION ; 
 int iwl_pcie_load_section (struct iwl_trans*,int,TYPE_1__*) ; 

__attribute__((used)) static int iwl_pcie_load_cpu_sections(struct iwl_trans *trans,
				      const struct fw_img *image,
				      int cpu,
				      int *first_ucode_section)
{
	int i, ret = 0;
	u32 last_read_idx = 0;

	if (cpu == 1)
		*first_ucode_section = 0;
	else
		(*first_ucode_section)++;

	for (i = *first_ucode_section; i < image->num_sec; i++) {
		last_read_idx = i;

		/*
		 * CPU1_CPU2_SEPARATOR_SECTION delimiter - separate between
		 * CPU1 to CPU2.
		 * PAGING_SEPARATOR_SECTION delimiter - separate between
		 * CPU2 non paged to CPU2 paging sec.
		 */
		if (!image->sec[i].data ||
		    image->sec[i].offset == CPU1_CPU2_SEPARATOR_SECTION ||
		    image->sec[i].offset == PAGING_SEPARATOR_SECTION) {
			IWL_DEBUG_FW(trans,
				     "Break since Data not valid or Empty section, sec = %d\n",
				     i);
			break;
		}

		ret = iwl_pcie_load_section(trans, i, &image->sec[i]);
		if (ret)
			return ret;
	}

	*first_ucode_section = last_read_idx;

	return 0;
}