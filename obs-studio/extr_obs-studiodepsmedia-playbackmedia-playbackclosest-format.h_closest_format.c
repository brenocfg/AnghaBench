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
#define  AV_PIX_FMT_BGR0 163 
#define  AV_PIX_FMT_BGRA 162 
#define  AV_PIX_FMT_NV12 161 
#define  AV_PIX_FMT_NV21 160 
#define  AV_PIX_FMT_RGBA 159 
#define  AV_PIX_FMT_UYVY422 158 
#define  AV_PIX_FMT_UYYVYY411 157 
#define  AV_PIX_FMT_YUV410P 156 
#define  AV_PIX_FMT_YUV411P 155 
#define  AV_PIX_FMT_YUV420P 154 
#define  AV_PIX_FMT_YUV420P10BE 153 
#define  AV_PIX_FMT_YUV420P10LE 152 
#define  AV_PIX_FMT_YUV420P12BE 151 
#define  AV_PIX_FMT_YUV420P12LE 150 
#define  AV_PIX_FMT_YUV420P14BE 149 
#define  AV_PIX_FMT_YUV420P14LE 148 
#define  AV_PIX_FMT_YUV420P16BE 147 
#define  AV_PIX_FMT_YUV420P16LE 146 
#define  AV_PIX_FMT_YUV420P9BE 145 
#define  AV_PIX_FMT_YUV420P9LE 144 
#define  AV_PIX_FMT_YUV422P 143 
#define  AV_PIX_FMT_YUV422P10BE 142 
#define  AV_PIX_FMT_YUV422P10LE 141 
#define  AV_PIX_FMT_YUV422P12BE 140 
#define  AV_PIX_FMT_YUV422P12LE 139 
#define  AV_PIX_FMT_YUV422P14BE 138 
#define  AV_PIX_FMT_YUV422P14LE 137 
#define  AV_PIX_FMT_YUV422P16BE 136 
#define  AV_PIX_FMT_YUV422P16LE 135 
#define  AV_PIX_FMT_YUV422P9BE 134 
#define  AV_PIX_FMT_YUV422P9LE 133 
#define  AV_PIX_FMT_YUV444P 132 
#define  AV_PIX_FMT_YUVJ420P 131 
#define  AV_PIX_FMT_YUVJ422P 130 
#define  AV_PIX_FMT_YUYV422 129 
#define  AV_PIX_FMT_YVYU422 128 

__attribute__((used)) static enum AVPixelFormat closest_format(enum AVPixelFormat fmt)
{
	switch (fmt) {
	case AV_PIX_FMT_YUYV422:
		return AV_PIX_FMT_YUYV422;
	case AV_PIX_FMT_YUV444P:
		return AV_PIX_FMT_YUV444P;

	case AV_PIX_FMT_YUV422P:
	case AV_PIX_FMT_YUVJ422P:
	case AV_PIX_FMT_UYVY422:
	case AV_PIX_FMT_YUV422P16LE:
	case AV_PIX_FMT_YUV422P16BE:
	case AV_PIX_FMT_YUV422P10BE:
	case AV_PIX_FMT_YUV422P10LE:
	case AV_PIX_FMT_YUV422P9BE:
	case AV_PIX_FMT_YUV422P9LE:
	case AV_PIX_FMT_YVYU422:
	case AV_PIX_FMT_YUV422P12BE:
	case AV_PIX_FMT_YUV422P12LE:
	case AV_PIX_FMT_YUV422P14BE:
	case AV_PIX_FMT_YUV422P14LE:
		return AV_PIX_FMT_UYVY422;

	case AV_PIX_FMT_NV12:
	case AV_PIX_FMT_NV21:
		return AV_PIX_FMT_NV12;

	case AV_PIX_FMT_YUV420P:
	case AV_PIX_FMT_YUVJ420P:
	case AV_PIX_FMT_YUV411P:
	case AV_PIX_FMT_UYYVYY411:
	case AV_PIX_FMT_YUV410P:
	case AV_PIX_FMT_YUV420P16LE:
	case AV_PIX_FMT_YUV420P16BE:
	case AV_PIX_FMT_YUV420P9BE:
	case AV_PIX_FMT_YUV420P9LE:
	case AV_PIX_FMT_YUV420P10BE:
	case AV_PIX_FMT_YUV420P10LE:
	case AV_PIX_FMT_YUV420P12BE:
	case AV_PIX_FMT_YUV420P12LE:
	case AV_PIX_FMT_YUV420P14BE:
	case AV_PIX_FMT_YUV420P14LE:
		return AV_PIX_FMT_YUV420P;

	case AV_PIX_FMT_RGBA:
	case AV_PIX_FMT_BGRA:
	case AV_PIX_FMT_BGR0:
		return fmt;

	default:
		break;
	}

	return AV_PIX_FMT_BGRA;
}