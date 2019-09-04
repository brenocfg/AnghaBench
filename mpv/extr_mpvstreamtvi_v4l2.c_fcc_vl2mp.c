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
 int MP_FOURCC_BGR15 ; 
 int MP_FOURCC_BGR16 ; 
 int MP_FOURCC_BGR24 ; 
 int MP_FOURCC_BGR32 ; 
 int MP_FOURCC_I420 ; 
 int MP_FOURCC_JPEG ; 
 int MP_FOURCC_MJPEG ; 
 int MP_FOURCC_RGB24 ; 
 int MP_FOURCC_RGB32 ; 
 int MP_FOURCC_RGB8 ; 
 int MP_FOURCC_UYVY ; 
 int MP_FOURCC_Y800 ; 
 int MP_FOURCC_YUV9 ; 
 int MP_FOURCC_YUY2 ; 
 int MP_FOURCC_YV12 ; 
#define  V4L2_PIX_FMT_BGR24 142 
#define  V4L2_PIX_FMT_BGR32 141 
#define  V4L2_PIX_FMT_GREY 140 
#define  V4L2_PIX_FMT_JPEG 139 
#define  V4L2_PIX_FMT_MJPEG 138 
#define  V4L2_PIX_FMT_RGB24 137 
#define  V4L2_PIX_FMT_RGB32 136 
#define  V4L2_PIX_FMT_RGB332 135 
#define  V4L2_PIX_FMT_RGB555 134 
#define  V4L2_PIX_FMT_RGB565 133 
#define  V4L2_PIX_FMT_UYVY 132 
#define  V4L2_PIX_FMT_YUV410 131 
#define  V4L2_PIX_FMT_YUV420 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVU420 128 

__attribute__((used)) static int fcc_vl2mp(int fcc)
{
    switch (fcc) {
    case V4L2_PIX_FMT_RGB332:   return MP_FOURCC_RGB8;
    case V4L2_PIX_FMT_RGB555:   return MP_FOURCC_BGR15;
    case V4L2_PIX_FMT_RGB565:   return MP_FOURCC_BGR16;
    case V4L2_PIX_FMT_RGB24:    return MP_FOURCC_RGB24;
    case V4L2_PIX_FMT_RGB32:    return MP_FOURCC_RGB32;
    case V4L2_PIX_FMT_BGR24:    return MP_FOURCC_BGR24;
    case V4L2_PIX_FMT_BGR32:    return MP_FOURCC_BGR32;
    case V4L2_PIX_FMT_GREY:     return MP_FOURCC_Y800;
    case V4L2_PIX_FMT_YUV410:   return MP_FOURCC_YUV9;
    case V4L2_PIX_FMT_YUV420:   return MP_FOURCC_I420;
    case V4L2_PIX_FMT_YVU420:   return MP_FOURCC_YV12;
    case V4L2_PIX_FMT_YUYV:     return MP_FOURCC_YUY2;
    case V4L2_PIX_FMT_UYVY:     return MP_FOURCC_UYVY;
    case V4L2_PIX_FMT_MJPEG:    return MP_FOURCC_MJPEG;
    case V4L2_PIX_FMT_JPEG:     return MP_FOURCC_JPEG;
    }
    return fcc;
}