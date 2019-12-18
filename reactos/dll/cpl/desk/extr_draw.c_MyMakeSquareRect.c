#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int right; int left; int bottom; int top; } ;
typedef  TYPE_1__* LPRECT ;

/* Variables and functions */

__attribute__((used)) static int
MyMakeSquareRect(LPRECT src, LPRECT dst)
{
    int Width  = src->right - src->left;
    int Height = src->bottom - src->top;
    int SmallDiam = Width > Height ? Height : Width;

    *dst = *src;

    /* Make it a square box */
    if (Width < Height)      /* SmallDiam == Width */
    {
        dst->top += (Height-Width)/2;
        dst->bottom = dst->top + SmallDiam;
    }
    else if (Width > Height) /* SmallDiam == Height */
    {
        dst->left += (Width-Height)/2;
        dst->right = dst->left + SmallDiam;
    }

    return SmallDiam;
}