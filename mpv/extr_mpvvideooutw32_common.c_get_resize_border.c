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
#define  WMSZ_BOTTOM 135 
#define  WMSZ_BOTTOMLEFT 134 
#define  WMSZ_BOTTOMRIGHT 133 
#define  WMSZ_LEFT 132 
#define  WMSZ_RIGHT 131 
#define  WMSZ_TOP 130 
#define  WMSZ_TOPLEFT 129 
#define  WMSZ_TOPRIGHT 128 

__attribute__((used)) static int get_resize_border(int v)
{
    switch (v) {
    case WMSZ_LEFT: return 3;
    case WMSZ_TOP: return 2;
    case WMSZ_RIGHT: return 3;
    case WMSZ_BOTTOM: return 2;
    case WMSZ_TOPLEFT: return 1;
    case WMSZ_TOPRIGHT: return 1;
    case WMSZ_BOTTOMLEFT: return 3;
    case WMSZ_BOTTOMRIGHT: return 3;
    default: return -1;
    }
}