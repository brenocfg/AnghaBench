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
struct vpfe_ipipeif_device {scalar_t__ input; struct v4l2_mbus_framefmt* formats; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; } ;

/* Variables and functions */
 int IPIPEIF_CCDC ; 
 scalar_t__ IPIPEIF_INPUT_MEMORY ; 
 size_t IPIPEIF_PAD_SINK ; 
 int IPIPEIF_SRC1_PARALLEL_PORT ; 
 scalar_t__ MEDIA_BUS_FMT_UV8_1X8 ; 
 scalar_t__ MEDIA_BUS_FMT_Y8_1X8 ; 

__attribute__((used)) static int
ipipeif_get_cfg_src1(struct vpfe_ipipeif_device *ipipeif)
{
	struct v4l2_mbus_framefmt *informat;

	informat = &ipipeif->formats[IPIPEIF_PAD_SINK];
	if (ipipeif->input == IPIPEIF_INPUT_MEMORY &&
	   (informat->code == MEDIA_BUS_FMT_Y8_1X8 ||
	    informat->code == MEDIA_BUS_FMT_UV8_1X8))
		return IPIPEIF_CCDC;

	return IPIPEIF_SRC1_PARALLEL_PORT;
}