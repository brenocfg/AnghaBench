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
typedef  int uint32_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
#define  DXGI_FORMAT_B8G8R8A8_UNORM 134 
#define  DXGI_FORMAT_B8G8R8X8_UNORM 133 
#define  DXGI_FORMAT_R10G10B10A2_UNORM 132 
#define  DXGI_FORMAT_R16G16B16A16_FLOAT 131 
#define  DXGI_FORMAT_R16G16B16A16_UNORM 130 
#define  DXGI_FORMAT_R32G32B32A32_FLOAT 129 
#define  DXGI_FORMAT_R8G8B8A8_UNORM 128 
 int GS_BGRA ; 
 int GS_BGRX ; 
 int GS_R10G10B10A2 ; 
 int GS_RGBA ; 
 int GS_RGBA16 ; 
 int GS_RGBA16F ; 
 int GS_RGBA32F ; 
 int GS_UNKNOWN ; 

__attribute__((used)) static inline enum gs_color_format convert_format(uint32_t format)
{
	switch (format) {
	case DXGI_FORMAT_R8G8B8A8_UNORM:     return GS_RGBA;
	case DXGI_FORMAT_B8G8R8X8_UNORM:     return GS_BGRX;
	case DXGI_FORMAT_B8G8R8A8_UNORM:     return GS_BGRA;
	case DXGI_FORMAT_R10G10B10A2_UNORM:  return GS_R10G10B10A2;
	case DXGI_FORMAT_R16G16B16A16_UNORM: return GS_RGBA16;
	case DXGI_FORMAT_R16G16B16A16_FLOAT: return GS_RGBA16F;
	case DXGI_FORMAT_R32G32B32A32_FLOAT: return GS_RGBA32F;
	}

	return GS_UNKNOWN;
}