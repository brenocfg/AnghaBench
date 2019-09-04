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
struct imx_media_dev {int dummy; } ;

/* Variables and functions */
 int add_ipu_internal_subdevs (struct imx_media_dev*,int) ; 
 int /*<<< orphan*/  imx_media_remove_internal_subdevs (struct imx_media_dev*) ; 

int imx_media_add_internal_subdevs(struct imx_media_dev *imxmd)
{
	int ret;

	ret = add_ipu_internal_subdevs(imxmd, 0);
	if (ret)
		goto remove;

	ret = add_ipu_internal_subdevs(imxmd, 1);
	if (ret)
		goto remove;

	return 0;

remove:
	imx_media_remove_internal_subdevs(imxmd);
	return ret;
}