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
typedef  enum video_colorspace { ____Placeholder_video_colorspace } video_colorspace ;
typedef  int /*<<< orphan*/ * CFStringRef ;

/* Variables and functions */
 int VIDEO_CS_601 ; 
 int VIDEO_CS_709 ; 
 int /*<<< orphan*/ * kCVImageBufferYCbCrMatrix_ITU_R_601_4 ; 
 int /*<<< orphan*/ * kCVImageBufferYCbCrMatrix_ITU_R_709_2 ; 

__attribute__((used)) static CFStringRef obs_to_vt_colorspace(enum video_colorspace cs)
{
	if (cs == VIDEO_CS_709)
		return kCVImageBufferYCbCrMatrix_ITU_R_709_2;
	else if (cs == VIDEO_CS_601)
		return kCVImageBufferYCbCrMatrix_ITU_R_601_4;

	return NULL;
}