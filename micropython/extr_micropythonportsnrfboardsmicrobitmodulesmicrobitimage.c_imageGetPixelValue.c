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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  mp_int_t ;
struct TYPE_4__ {scalar_t__ five; } ;
struct TYPE_5__ {int /*<<< orphan*/  greyscale; int /*<<< orphan*/  monochrome_5by5; TYPE_1__ base; } ;
typedef  TYPE_2__ microbit_image_obj_t ;

/* Variables and functions */
 int MAX_BRIGHTNESS ; 
 int greyscaleGetPixelValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int monochromeGetPixelValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint8_t imageGetPixelValue(microbit_image_obj_t * p_image, mp_int_t x, mp_int_t y) {
    if (p_image->base.five)
        return monochromeGetPixelValue(&p_image->monochrome_5by5, x, y)*MAX_BRIGHTNESS;
    else
        return greyscaleGetPixelValue(&p_image->greyscale, x, y);
}