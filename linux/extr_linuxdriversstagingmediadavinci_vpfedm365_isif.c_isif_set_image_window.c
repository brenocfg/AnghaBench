#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct TYPE_11__ {TYPE_4__ win; } ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct TYPE_9__ {TYPE_2__ win; } ;
struct TYPE_12__ {TYPE_5__ ycbcr; TYPE_3__ bayer; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct vpfe_isif_device {TYPE_6__ isif_cfg; TYPE_1__* formats; struct v4l2_rect crop; } ;
struct TYPE_7__ {scalar_t__ code; } ;

/* Variables and functions */
 size_t ISIF_PAD_SINK ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 

__attribute__((used)) static int isif_set_image_window(struct vpfe_isif_device *isif)
{
	struct v4l2_rect *win = &isif->crop;

	if (isif->formats[ISIF_PAD_SINK].code == MEDIA_BUS_FMT_SGRBG12_1X12) {
		isif->isif_cfg.bayer.win.top = win->top;
		isif->isif_cfg.bayer.win.left = win->left;
		isif->isif_cfg.bayer.win.width = win->width;
		isif->isif_cfg.bayer.win.height = win->height;
		return 0;
	}
	isif->isif_cfg.ycbcr.win.top = win->top;
	isif->isif_cfg.ycbcr.win.left = win->left;
	isif->isif_cfg.ycbcr.win.width = win->width;
	isif->isif_cfg.ycbcr.win.height = win->height;

	return 0;
}