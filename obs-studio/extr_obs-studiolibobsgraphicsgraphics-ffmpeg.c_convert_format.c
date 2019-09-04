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
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
#define  AV_PIX_FMT_BGR0 130 
#define  AV_PIX_FMT_BGRA 129 
#define  AV_PIX_FMT_RGBA 128 
 int GS_BGRA ; 
 int GS_BGRX ; 
 int GS_RGBA ; 

__attribute__((used)) static inline enum gs_color_format convert_format(enum AVPixelFormat format)
{
	switch ((int)format) {
	case AV_PIX_FMT_RGBA: return GS_RGBA;
	case AV_PIX_FMT_BGRA: return GS_BGRA;
	case AV_PIX_FMT_BGR0: return GS_BGRX;
	}

	return GS_BGRX;
}