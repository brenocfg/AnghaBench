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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum video_format { ____Placeholder_video_format } video_format ;

/* Variables and functions */
 int /*<<< orphan*/  CHROMA_CONV (char*,char*,int) ; 
 int /*<<< orphan*/  CHROMA_CONV_FULL (char*,char*,int) ; 
 int /*<<< orphan*/  CHROMA_TEST (char*,int) ; 
 int VIDEO_FORMAT_BGRA ; 
 int VIDEO_FORMAT_I420 ; 
 int VIDEO_FORMAT_I444 ; 
 int VIDEO_FORMAT_NV12 ; 
 int VIDEO_FORMAT_RGBA ; 
 int VIDEO_FORMAT_UYVY ; 
 int VIDEO_FORMAT_Y800 ; 
 int VIDEO_FORMAT_YUY2 ; 
 int VIDEO_FORMAT_YVYU ; 

__attribute__((used)) static enum video_format convert_vlc_video_format(char *chroma, bool *full)
{
	*full = false;

#define CHROMA_TEST(val, ret)       \
	if (chroma_is(chroma, val)) \
	return ret
#define CHROMA_CONV(val, new_val, ret)                              \
	do {                                                        \
		if (chroma_is(chroma, val)) {                       \
			*(uint32_t *)chroma = *(uint32_t *)new_val; \
			return ret;                                 \
		}                                                   \
	} while (false)
#define CHROMA_CONV_FULL(val, new_val, ret)     \
	do {                                    \
		*full = true;                   \
		CHROMA_CONV(val, new_val, ret); \
	} while (false)

	CHROMA_TEST("RGBA", VIDEO_FORMAT_RGBA);
	CHROMA_TEST("BGRA", VIDEO_FORMAT_BGRA);

	/* 4:2:0 formats */
	CHROMA_TEST("NV12", VIDEO_FORMAT_NV12);
	CHROMA_TEST("I420", VIDEO_FORMAT_I420);
	CHROMA_TEST("IYUV", VIDEO_FORMAT_I420);
	CHROMA_CONV("NV21", "NV12", VIDEO_FORMAT_NV12);
	CHROMA_CONV("I422", "NV12", VIDEO_FORMAT_NV12);
	CHROMA_CONV("Y42B", "NV12", VIDEO_FORMAT_NV12);
	CHROMA_CONV("YV12", "NV12", VIDEO_FORMAT_NV12);
	CHROMA_CONV("yv12", "NV12", VIDEO_FORMAT_NV12);

	CHROMA_CONV_FULL("J420", "J420", VIDEO_FORMAT_I420);

	/* 4:2:2 formats */
	CHROMA_TEST("UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_TEST("UYNV", VIDEO_FORMAT_UYVY);
	CHROMA_TEST("UYNY", VIDEO_FORMAT_UYVY);
	CHROMA_TEST("Y422", VIDEO_FORMAT_UYVY);
	CHROMA_TEST("HDYC", VIDEO_FORMAT_UYVY);
	CHROMA_TEST("AVUI", VIDEO_FORMAT_UYVY);
	CHROMA_TEST("uyv1", VIDEO_FORMAT_UYVY);
	CHROMA_TEST("2vuy", VIDEO_FORMAT_UYVY);
	CHROMA_TEST("2Vuy", VIDEO_FORMAT_UYVY);
	CHROMA_TEST("2Vu1", VIDEO_FORMAT_UYVY);

	CHROMA_TEST("YUY2", VIDEO_FORMAT_YUY2);
	CHROMA_TEST("YUYV", VIDEO_FORMAT_YUY2);
	CHROMA_TEST("YUNV", VIDEO_FORMAT_YUY2);
	CHROMA_TEST("V422", VIDEO_FORMAT_YUY2);

	CHROMA_TEST("YVYU", VIDEO_FORMAT_YVYU);

	CHROMA_CONV("v210", "UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("cyuv", "UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("CYUV", "UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("VYUY", "UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("NV16", "UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("NV61", "UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("I410", "UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("I422", "UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("Y42B", "UYVY", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("J422", "UYVY", VIDEO_FORMAT_UYVY);

	/* 4:4:4 formats */
	CHROMA_TEST("I444", VIDEO_FORMAT_I444);
	CHROMA_CONV_FULL("J444", "RGBA", VIDEO_FORMAT_RGBA);
	CHROMA_CONV("YUVA", "RGBA", VIDEO_FORMAT_RGBA);

	/* 4:4:0 formats */
	CHROMA_CONV("I440", "I444", VIDEO_FORMAT_I444);
	CHROMA_CONV("J440", "I444", VIDEO_FORMAT_I444);

	/* 4:1:0 formats */
	CHROMA_CONV("YVU9", "NV12", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("I410", "NV12", VIDEO_FORMAT_UYVY);

	/* 4:1:1 formats */
	CHROMA_CONV("I411", "NV12", VIDEO_FORMAT_UYVY);
	CHROMA_CONV("Y41B", "NV12", VIDEO_FORMAT_UYVY);

	/* greyscale formats */
	CHROMA_TEST("GREY", VIDEO_FORMAT_Y800);
	CHROMA_TEST("Y800", VIDEO_FORMAT_Y800);
	CHROMA_TEST("Y8  ", VIDEO_FORMAT_Y800);
#undef CHROMA_CONV_FULL
#undef CHROMA_CONV
#undef CHROMA_TEST

	*(uint32_t *)chroma = *(uint32_t *)"BGRA";
	return VIDEO_FORMAT_BGRA;
}