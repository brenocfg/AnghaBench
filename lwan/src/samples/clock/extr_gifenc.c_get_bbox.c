#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int w; int h; scalar_t__* frame; scalar_t__* back; } ;
typedef  TYPE_1__ ge_GIF ;

/* Variables and functions */

__attribute__((used)) static int
get_bbox(ge_GIF *gif, uint16_t *w, uint16_t *h, uint16_t *x, uint16_t *y)
{
    int i, j, k;
    int left, right, top, bottom;

    left = gif->w;
    right = 0;
    top = gif->h;
    bottom = 0;
    k = 0;
    for (i = 0; i < gif->h; i++) {
        for (j = 0; j < gif->w; j++, k++) {
            if (gif->frame[k] != gif->back[k]) {
                if (j < left)
                    left = j;
                if (j > right)
                    right = j;
                if (i < top)
                    top = i;
                if (i > bottom)
                    bottom = i;
            }
        }
    }

    if (left != gif->w && top != gif->h) {
        *x = left;
        *y = top;
        *w = right - left + 1;
        *h = bottom - top + 1;
        return 1;
    } else {
        return 0;
    }
}