#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ decimal; scalar_t__ integer; } ;
struct TYPE_17__ {scalar_t__ decimal; scalar_t__ integer; } ;
struct TYPE_16__ {scalar_t__ decimal; scalar_t__ integer; } ;
struct TYPE_15__ {scalar_t__ decimal; scalar_t__ integer; } ;
struct TYPE_14__ {scalar_t__ decimal; scalar_t__ integer; } ;
struct TYPE_13__ {scalar_t__ decimal; scalar_t__ integer; } ;
struct TYPE_12__ {scalar_t__ decimal; scalar_t__ integer; } ;
struct TYPE_11__ {scalar_t__ decimal; scalar_t__ integer; } ;
struct TYPE_10__ {scalar_t__ decimal; scalar_t__ integer; } ;
struct vpfe_ipipe_rgb2yuv {scalar_t__ out_ofst_y; scalar_t__ out_ofst_cb; scalar_t__ out_ofst_cr; TYPE_9__ coef_bcr; TYPE_8__ coef_gcr; TYPE_7__ coef_rcr; TYPE_6__ coef_bcb; TYPE_5__ coef_gcb; TYPE_4__ coef_rcb; TYPE_3__ coef_by; TYPE_2__ coef_gy; TYPE_1__ coef_ry; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RGB2YCBCR_COEF_DECI_MASK ; 
 scalar_t__ RGB2YCBCR_COEF_INT_MASK ; 
 scalar_t__ RGB2YCBCR_OFST_MASK ; 

__attribute__((used)) static int ipipe_validate_rgb2yuv_params(struct vpfe_ipipe_rgb2yuv *rgb2yuv)
{
	if (rgb2yuv->coef_ry.decimal > RGB2YCBCR_COEF_DECI_MASK ||
	   rgb2yuv->coef_ry.integer > RGB2YCBCR_COEF_INT_MASK)
		return -EINVAL;

	if (rgb2yuv->coef_gy.decimal > RGB2YCBCR_COEF_DECI_MASK ||
	   rgb2yuv->coef_gy.integer > RGB2YCBCR_COEF_INT_MASK)
		return -EINVAL;

	if (rgb2yuv->coef_by.decimal > RGB2YCBCR_COEF_DECI_MASK ||
	   rgb2yuv->coef_by.integer > RGB2YCBCR_COEF_INT_MASK)
		return -EINVAL;

	if (rgb2yuv->coef_rcb.decimal > RGB2YCBCR_COEF_DECI_MASK ||
	   rgb2yuv->coef_rcb.integer > RGB2YCBCR_COEF_INT_MASK)
		return -EINVAL;

	if (rgb2yuv->coef_gcb.decimal > RGB2YCBCR_COEF_DECI_MASK ||
	   rgb2yuv->coef_gcb.integer > RGB2YCBCR_COEF_INT_MASK)
		return -EINVAL;

	if (rgb2yuv->coef_bcb.decimal > RGB2YCBCR_COEF_DECI_MASK ||
	   rgb2yuv->coef_bcb.integer > RGB2YCBCR_COEF_INT_MASK)
		return -EINVAL;

	if (rgb2yuv->coef_rcr.decimal > RGB2YCBCR_COEF_DECI_MASK ||
	   rgb2yuv->coef_rcr.integer > RGB2YCBCR_COEF_INT_MASK)
		return -EINVAL;

	if (rgb2yuv->coef_gcr.decimal > RGB2YCBCR_COEF_DECI_MASK ||
	   rgb2yuv->coef_gcr.integer > RGB2YCBCR_COEF_INT_MASK)
		return -EINVAL;

	if (rgb2yuv->coef_bcr.decimal > RGB2YCBCR_COEF_DECI_MASK ||
	   rgb2yuv->coef_bcr.integer > RGB2YCBCR_COEF_INT_MASK)
		return -EINVAL;

	if (rgb2yuv->out_ofst_y > RGB2YCBCR_OFST_MASK ||
	   rgb2yuv->out_ofst_cb > RGB2YCBCR_OFST_MASK ||
	   rgb2yuv->out_ofst_cr > RGB2YCBCR_OFST_MASK)
		return -EINVAL;

	return 0;
}