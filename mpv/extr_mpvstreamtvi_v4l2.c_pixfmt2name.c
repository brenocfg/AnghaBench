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

/* Variables and functions */
#define  V4L2_PIX_FMT_BGR24 153 
#define  V4L2_PIX_FMT_BGR32 152 
#define  V4L2_PIX_FMT_GREY 151 
#define  V4L2_PIX_FMT_HI240 150 
#define  V4L2_PIX_FMT_JPEG 149 
#define  V4L2_PIX_FMT_MJPEG 148 
#define  V4L2_PIX_FMT_NV12 147 
#define  V4L2_PIX_FMT_NV21 146 
#define  V4L2_PIX_FMT_RGB24 145 
#define  V4L2_PIX_FMT_RGB32 144 
#define  V4L2_PIX_FMT_RGB332 143 
#define  V4L2_PIX_FMT_RGB555 142 
#define  V4L2_PIX_FMT_RGB555X 141 
#define  V4L2_PIX_FMT_RGB565 140 
#define  V4L2_PIX_FMT_RGB565X 139 
#define  V4L2_PIX_FMT_UYVY 138 
#define  V4L2_PIX_FMT_WNVA 137 
#define  V4L2_PIX_FMT_Y41P 136 
#define  V4L2_PIX_FMT_YUV410 135 
#define  V4L2_PIX_FMT_YUV411P 134 
#define  V4L2_PIX_FMT_YUV420 133 
#define  V4L2_PIX_FMT_YUV422P 132 
#define  V4L2_PIX_FMT_YUYV 131 
#define  V4L2_PIX_FMT_YVU410 130 
#define  V4L2_PIX_FMT_YVU420 129 
#define  V4L2_PIX_FMT_YYUV 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static const char *pixfmt2name(char *buf, int pixfmt)
{
    switch (pixfmt) {
    case V4L2_PIX_FMT_RGB332:       return "RGB332";
    case V4L2_PIX_FMT_RGB555:       return "RGB555";
    case V4L2_PIX_FMT_RGB565:       return "RGB565";
    case V4L2_PIX_FMT_RGB555X:      return "RGB555X";
    case V4L2_PIX_FMT_RGB565X:      return "RGB565X";
    case V4L2_PIX_FMT_BGR24:        return "BGR24";
    case V4L2_PIX_FMT_RGB24:        return "RGB24";
    case V4L2_PIX_FMT_BGR32:        return "BGR32";
    case V4L2_PIX_FMT_RGB32:        return "RGB32";
    case V4L2_PIX_FMT_GREY:         return "GREY";
    case V4L2_PIX_FMT_YVU410:       return "YVU410";
    case V4L2_PIX_FMT_YVU420:       return "YVU420";
    case V4L2_PIX_FMT_YUYV:         return "YUYV";
    case V4L2_PIX_FMT_UYVY:         return "UYVY";
/*    case V4L2_PIX_FMT_YVU422P:      return "YVU422P"; */
/*    case V4L2_PIX_FMT_YVU411P:      return "YVU411P"; */
    case V4L2_PIX_FMT_YUV422P:      return "YUV422P";
    case V4L2_PIX_FMT_YUV411P:      return "YUV411P";
    case V4L2_PIX_FMT_Y41P:         return "Y41P";
    case V4L2_PIX_FMT_NV12:         return "NV12";
    case V4L2_PIX_FMT_NV21:         return "NV21";
    case V4L2_PIX_FMT_YUV410:       return "YUV410";
    case V4L2_PIX_FMT_YUV420:       return "YUV420";
    case V4L2_PIX_FMT_YYUV:         return "YYUV";
    case V4L2_PIX_FMT_HI240:        return "HI240";
    case V4L2_PIX_FMT_WNVA:         return "WNVA";
    case V4L2_PIX_FMT_MJPEG:        return "MJPEG";
    case V4L2_PIX_FMT_JPEG:         return "JPEG";
    }
    sprintf(buf, "unknown (0x%x)", pixfmt);
    return buf;
}