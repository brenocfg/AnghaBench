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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
#define  AV_PIX_FMT_YUV420P 130 
#define  AV_PIX_FMT_YUV422P 129 
#define  AV_PIX_FMT_YUV444P 128 
 int AV_PIX_FMT_YUVJ420P ; 
 int AV_PIX_FMT_YUVJ422P ; 
 int AV_PIX_FMT_YUVJ444P ; 

__attribute__((used)) static enum AVPixelFormat replace_j_format(enum AVPixelFormat fmt)
{
    switch (fmt) {
    case AV_PIX_FMT_YUV420P: return AV_PIX_FMT_YUVJ420P;
    case AV_PIX_FMT_YUV422P: return AV_PIX_FMT_YUVJ422P;
    case AV_PIX_FMT_YUV444P: return AV_PIX_FMT_YUVJ444P;
    }
    return fmt;
}