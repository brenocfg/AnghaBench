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
typedef  int uint8_t ;
typedef  size_t mp_int_t ;
typedef  int /*<<< orphan*/  microbit_image_obj_t ;
struct TYPE_3__ {int** image_buffer; size_t brightnesses; } ;
typedef  TYPE_1__ microbit_display_obj_t ;

/* Variables and functions */
 int imageGetPixelValue (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  imageHeight (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imageWidth (int /*<<< orphan*/ *) ; 
 size_t min (int /*<<< orphan*/ ,int) ; 

void microbit_display_show(microbit_display_obj_t *display, microbit_image_obj_t *image) {
    mp_int_t w = min(imageWidth(image), 5);
    mp_int_t h = min(imageHeight(image), 5);
    mp_int_t x = 0;
    mp_int_t brightnesses = 0;
    for (; x < w; ++x) {
        mp_int_t y = 0;
        for (; y < h; ++y) {
            uint8_t pix = imageGetPixelValue(image, x, y);
            display->image_buffer[x][y] = pix;
            brightnesses |= (1 << pix);
        }
        for (; y < 5; ++y) {
            display->image_buffer[x][y] = 0;
        }
    }
    for (; x < 5; ++x) {
        for (mp_int_t y = 0; y < 5; ++y) {
            display->image_buffer[x][y] = 0;
        }
    }
    display->brightnesses = brightnesses;
}