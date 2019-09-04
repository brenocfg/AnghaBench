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
#define  MP_FOURCC_BGR15 142 
#define  MP_FOURCC_BGR16 141 
#define  MP_FOURCC_BGR24 140 
#define  MP_FOURCC_BGR32 139 
#define  MP_FOURCC_I420 138 
#define  MP_FOURCC_JPEG 137 
#define  MP_FOURCC_MJPEG 136 
#define  MP_FOURCC_RGB24 135 
#define  MP_FOURCC_RGB32 134 
#define  MP_FOURCC_RGB8 133 
#define  MP_FOURCC_UYVY 132 
#define  MP_FOURCC_Y800 131 
#define  MP_FOURCC_YUV9 130 
#define  MP_FOURCC_YUY2 129 
#define  MP_FOURCC_YV12 128 
 int V4L2_PIX_FMT_BGR24 ; 
 int V4L2_PIX_FMT_BGR32 ; 
 int V4L2_PIX_FMT_GREY ; 
 int V4L2_PIX_FMT_JPEG ; 
 int V4L2_PIX_FMT_MJPEG ; 
 int V4L2_PIX_FMT_RGB24 ; 
 int V4L2_PIX_FMT_RGB32 ; 
 int V4L2_PIX_FMT_RGB332 ; 
 int V4L2_PIX_FMT_RGB555 ; 
 int V4L2_PIX_FMT_RGB565 ; 
 int V4L2_PIX_FMT_UYVY ; 
 int V4L2_PIX_FMT_YUV410 ; 
 int V4L2_PIX_FMT_YUV420 ; 
 int V4L2_PIX_FMT_YUYV ; 
 int V4L2_PIX_FMT_YVU420 ; 

__attribute__((used)) static int fcc_mp2vl(int fcc)
{
    switch (fcc) {
    case MP_FOURCC_RGB8:   return V4L2_PIX_FMT_RGB332;
    case MP_FOURCC_BGR15:  return V4L2_PIX_FMT_RGB555;
    case MP_FOURCC_BGR16:  return V4L2_PIX_FMT_RGB565;
    case MP_FOURCC_RGB24:  return V4L2_PIX_FMT_RGB24;
    case MP_FOURCC_RGB32:  return V4L2_PIX_FMT_RGB32;
    case MP_FOURCC_BGR24:  return V4L2_PIX_FMT_BGR24;
    case MP_FOURCC_BGR32:  return V4L2_PIX_FMT_BGR32;
    case MP_FOURCC_Y800:   return V4L2_PIX_FMT_GREY;
    case MP_FOURCC_YUV9:   return V4L2_PIX_FMT_YUV410;
    case MP_FOURCC_I420:   return V4L2_PIX_FMT_YUV420;
    case MP_FOURCC_YUY2:   return V4L2_PIX_FMT_YUYV;
    case MP_FOURCC_YV12:   return V4L2_PIX_FMT_YVU420;
    case MP_FOURCC_UYVY:   return V4L2_PIX_FMT_UYVY;
    case MP_FOURCC_MJPEG:  return V4L2_PIX_FMT_MJPEG;
    case MP_FOURCC_JPEG:   return V4L2_PIX_FMT_JPEG;
    }
    return fcc;
}