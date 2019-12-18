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

/* Variables and functions */
#define  GBM_FORMAT_ARGB2101010 131 
#define  GBM_FORMAT_ARGB8888 130 
#define  GBM_FORMAT_XRGB2101010 129 
#define  GBM_FORMAT_XRGB8888 128 

__attribute__((used)) static uint32_t fallback_format_for(uint32_t format)
{
    switch (format) {
    case GBM_FORMAT_XRGB8888:
        return GBM_FORMAT_ARGB8888;
    case GBM_FORMAT_ARGB8888:
        return GBM_FORMAT_XRGB8888;
    case GBM_FORMAT_XRGB2101010:
        return GBM_FORMAT_ARGB2101010;
    case GBM_FORMAT_ARGB2101010:
        return GBM_FORMAT_XRGB2101010;
    default:
        return 0;
    }
}