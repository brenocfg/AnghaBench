#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hw_flags; } ;
struct mp_image {TYPE_2__ params; TYPE_1__* hwctx; } ;
struct TYPE_6__ {scalar_t__ sw_format; } ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_3__ AVHWFramesContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  MP_IMAGE_HW_FLAG_OPAQUE ; 

__attribute__((used)) static void d3d11_complete_image_params(struct mp_image *img)
{
    AVHWFramesContext *hw_frames = (void *)img->hwctx->data;

    // According to hwcontex_d3d11va.h, this means DXGI_FORMAT_420_OPAQUE.
    img->params.hw_flags = hw_frames->sw_format == AV_PIX_FMT_YUV420P
                         ? MP_IMAGE_HW_FLAG_OPAQUE : 0;
}