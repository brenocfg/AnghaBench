#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_2__ {size_t r; size_t g; size_t b; } ;

/* Variables and functions */
 TYPE_1__* led ; 

void rgbsps_set(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  led[index].r = r;
  led[index].g = g;
  led[index].b = b;
}