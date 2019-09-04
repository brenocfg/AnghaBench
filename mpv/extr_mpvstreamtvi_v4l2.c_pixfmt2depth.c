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
#define  V4L2_PIX_FMT_BGR24 150 
#define  V4L2_PIX_FMT_BGR32 149 
#define  V4L2_PIX_FMT_GREY 148 
#define  V4L2_PIX_FMT_HI240 147 
#define  V4L2_PIX_FMT_NV12 146 
#define  V4L2_PIX_FMT_NV21 145 
#define  V4L2_PIX_FMT_RGB24 144 
#define  V4L2_PIX_FMT_RGB32 143 
#define  V4L2_PIX_FMT_RGB332 142 
#define  V4L2_PIX_FMT_RGB555 141 
#define  V4L2_PIX_FMT_RGB555X 140 
#define  V4L2_PIX_FMT_RGB565 139 
#define  V4L2_PIX_FMT_RGB565X 138 
#define  V4L2_PIX_FMT_UYVY 137 
#define  V4L2_PIX_FMT_Y41P 136 
#define  V4L2_PIX_FMT_YUV410 135 
#define  V4L2_PIX_FMT_YUV411P 134 
#define  V4L2_PIX_FMT_YUV420 133 
#define  V4L2_PIX_FMT_YUV422P 132 
#define  V4L2_PIX_FMT_YUYV 131 
#define  V4L2_PIX_FMT_YVU410 130 
#define  V4L2_PIX_FMT_YVU420 129 
#define  V4L2_PIX_FMT_YYUV 128 

__attribute__((used)) static int pixfmt2depth(int pixfmt)
{
    switch (pixfmt) {
    case V4L2_PIX_FMT_RGB332:
        return 8;
    case V4L2_PIX_FMT_RGB555:
    case V4L2_PIX_FMT_RGB565:
    case V4L2_PIX_FMT_RGB555X:
    case V4L2_PIX_FMT_RGB565X:
        return 16;
    case V4L2_PIX_FMT_BGR24:
    case V4L2_PIX_FMT_RGB24:
        return 24;
    case V4L2_PIX_FMT_BGR32:
    case V4L2_PIX_FMT_RGB32:
        return 32;
    case V4L2_PIX_FMT_GREY:
        return 8;
    case V4L2_PIX_FMT_YVU410:
        return 9;
    case V4L2_PIX_FMT_YVU420:
        return 12;
    case V4L2_PIX_FMT_YUYV:
    case V4L2_PIX_FMT_UYVY:
    case V4L2_PIX_FMT_YUV422P:
    case V4L2_PIX_FMT_YUV411P:
        return 16;
    case V4L2_PIX_FMT_Y41P:
    case V4L2_PIX_FMT_NV12:
    case V4L2_PIX_FMT_NV21:
        return 12;
    case V4L2_PIX_FMT_YUV410:
        return 9;
    case V4L2_PIX_FMT_YUV420:
        return 12;
    case V4L2_PIX_FMT_YYUV:
        return 16;
    case V4L2_PIX_FMT_HI240:
        return 8;

    }
    return 0;
}