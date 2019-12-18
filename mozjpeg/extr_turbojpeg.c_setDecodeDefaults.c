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
struct jpeg_decompress_struct {int scale_num; int scale_denom; int num_components; int comps_in_scan; int data_precision; int /*<<< orphan*/ ** quant_tbl_ptrs; TYPE_2__** cur_comp_info; TYPE_2__* comp_info; TYPE_1__* mem; int /*<<< orphan*/  jpeg_color_space; } ;
struct TYPE_4__ {int h_samp_factor; int v_samp_factor; int component_index; int component_id; int quant_tbl_no; int dc_tbl_no; int ac_tbl_no; } ;
typedef  TYPE_2__ jpeg_component_info ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_3__ {scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  JCS_GRAYSCALE ; 
 int /*<<< orphan*/  JCS_YCbCr ; 
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int TJSAMP_GRAY ; 
 int /*<<< orphan*/ * jpeg_alloc_quant_table (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* tjMCUHeight ; 
 int* tjMCUWidth ; 

__attribute__((used)) static int setDecodeDefaults(struct jpeg_decompress_struct *dinfo,
	int pixelFormat, int subsamp, int flags)
{
	int i;

	dinfo->scale_num=dinfo->scale_denom=1;

  if (subsamp == TJSAMP_GRAY) {
		dinfo->num_components=dinfo->comps_in_scan=1;
		dinfo->jpeg_color_space=JCS_GRAYSCALE;
  } else {
		dinfo->num_components=dinfo->comps_in_scan=3;
		dinfo->jpeg_color_space=JCS_YCbCr;
	}

	dinfo->comp_info=(jpeg_component_info *)
		(*dinfo->mem->alloc_small)((j_common_ptr)dinfo, JPOOL_IMAGE,
                                dinfo->num_components *
                                sizeof(jpeg_component_info));

  for (i = 0; i < dinfo->num_components; i++) {
		jpeg_component_info *compptr=&dinfo->comp_info[i];

		compptr->h_samp_factor=(i==0)? tjMCUWidth[subsamp]/8:1;
		compptr->v_samp_factor=(i==0)? tjMCUHeight[subsamp]/8:1;
		compptr->component_index=i;
		compptr->component_id=i+1;
    compptr->quant_tbl_no = compptr->dc_tbl_no =
      compptr->ac_tbl_no = (i == 0) ? 0 : 1;
		dinfo->cur_comp_info[i]=compptr;
	}
	dinfo->data_precision=8;
  for (i = 0; i < 2; i++) {
		if(dinfo->quant_tbl_ptrs[i]==NULL)
			dinfo->quant_tbl_ptrs[i]=jpeg_alloc_quant_table((j_common_ptr)dinfo);
	}

	return 0;
}