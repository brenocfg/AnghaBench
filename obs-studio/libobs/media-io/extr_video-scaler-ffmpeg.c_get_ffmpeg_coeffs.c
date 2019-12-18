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

/* Variables and functions */
 int /*<<< orphan*/  SWS_CS_ITU601 ; 
 int /*<<< orphan*/  SWS_CS_ITU709 ; 
#define  VIDEO_CS_601 130 
#define  VIDEO_CS_709 129 
#define  VIDEO_CS_DEFAULT 128 
 int const* sws_getCoefficients (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const int *get_ffmpeg_coeffs(enum video_colorspace cs)
{
	switch (cs) {
	case VIDEO_CS_DEFAULT:
		return sws_getCoefficients(SWS_CS_ITU601);
	case VIDEO_CS_601:
		return sws_getCoefficients(SWS_CS_ITU601);
	case VIDEO_CS_709:
		return sws_getCoefficients(SWS_CS_ITU709);
	}

	return sws_getCoefficients(SWS_CS_ITU601);
}