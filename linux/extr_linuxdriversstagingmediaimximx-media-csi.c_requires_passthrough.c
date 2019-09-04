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
struct v4l2_mbus_framefmt {scalar_t__ code; } ;
struct v4l2_fwnode_endpoint {int dummy; } ;
struct imx_media_pixfmt {scalar_t__ bayer; } ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_UYVY8_2X8 ; 
 scalar_t__ MEDIA_BUS_FMT_YUYV8_2X8 ; 
 scalar_t__ is_parallel_16bit_bus (struct v4l2_fwnode_endpoint*) ; 
 scalar_t__ is_parallel_bus (struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static inline bool requires_passthrough(struct v4l2_fwnode_endpoint *ep,
					struct v4l2_mbus_framefmt *infmt,
					const struct imx_media_pixfmt *incc)
{
	return incc->bayer || is_parallel_16bit_bus(ep) ||
		(is_parallel_bus(ep) &&
		 infmt->code != MEDIA_BUS_FMT_UYVY8_2X8 &&
		 infmt->code != MEDIA_BUS_FMT_YUYV8_2X8);
}