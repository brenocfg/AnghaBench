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
typedef  size_t uint8_t ;
struct TYPE_3__ {void* y; void* x; } ;
typedef  TYPE_1__ Point ;

/* Variables and functions */
 int /*<<< orphan*/ * g_map_led_to_point_polar ; 
 void* pgm_read_byte (size_t*) ; 

void map_led_to_point_polar( uint8_t index, Point *point )
{
    // Slightly messy way to get Point structs out of progmem.
    uint8_t *addr = (uint8_t*)&g_map_led_to_point_polar[index];
    point->x = pgm_read_byte(addr);
    point->y = pgm_read_byte(addr+1);
}