#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {size_t prop_count; TYPE_1__* prop_item; } ;
struct TYPE_4__ {scalar_t__ id; int length; scalar_t__ value; } ;
typedef  TYPE_2__ GpBitmap ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ PropertyTagGlobalPalette ; 
 scalar_t__ PropertyTagIndexBackground ; 
 scalar_t__ PropertyTagIndexTransparent ; 

__attribute__((used)) static DWORD get_gif_background_color(GpBitmap *bitmap)
{
    BYTE bgcolor_idx = 0;
    UINT i;

    for(i=0; i<bitmap->prop_count; i++) {
        if(bitmap->prop_item[i].id == PropertyTagIndexBackground) {
            bgcolor_idx = *(BYTE*)bitmap->prop_item[i].value;
            break;
        }
    }

    for(i=0; i<bitmap->prop_count; i++) {
        if(bitmap->prop_item[i].id == PropertyTagIndexTransparent) {
            BYTE transparent_idx;
            transparent_idx = *(BYTE*)bitmap->prop_item[i].value;

            if(transparent_idx == bgcolor_idx)
                return 0;
        }
    }

    for(i=0; i<bitmap->prop_count; i++) {
        if(bitmap->prop_item[i].id == PropertyTagGlobalPalette) {
            if(bitmap->prop_item[i].length/3 > bgcolor_idx) {
                BYTE *color = ((BYTE*)bitmap->prop_item[i].value)+bgcolor_idx*3;
                return color[2] + (color[1]<<8) + (color[0]<<16) + (0xffu<<24);
            }
            break;
        }
    }

    FIXME("can't get gif background color\n");
    return 0xffffffff;
}