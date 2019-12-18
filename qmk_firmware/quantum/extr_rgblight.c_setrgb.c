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
typedef  void* uint8_t ;
struct TYPE_3__ {scalar_t__ w; void* b; void* g; void* r; } ;
typedef  TYPE_1__ LED_TYPE ;

/* Variables and functions */

void setrgb(uint8_t r, uint8_t g, uint8_t b, LED_TYPE *led1) {
    (*led1).r = r;
    (*led1).g = g;
    (*led1).b = b;
#ifdef RGBW
    (*led1).w = 0;
#endif
}