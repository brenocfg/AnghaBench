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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ipu_image {TYPE_1__ rect; int /*<<< orphan*/  pix; } ;

/* Variables and functions */
 int imx_media_mbus_fmt_to_pix_fmt (int /*<<< orphan*/ *,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ipu_image*,int /*<<< orphan*/ ,int) ; 

int imx_media_mbus_fmt_to_ipu_image(struct ipu_image *image,
				    struct v4l2_mbus_framefmt *mbus)
{
	int ret;

	memset(image, 0, sizeof(*image));

	ret = imx_media_mbus_fmt_to_pix_fmt(&image->pix, mbus, NULL);
	if (ret)
		return ret;

	image->rect.width = mbus->width;
	image->rect.height = mbus->height;

	return 0;
}