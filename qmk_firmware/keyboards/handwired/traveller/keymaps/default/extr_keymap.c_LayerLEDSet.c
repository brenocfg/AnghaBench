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
typedef  int uint8_t ;

/* Variables and functions */
#define  _FKEYS 132 
#define  _HI 131 
#define  _LW 130 
#define  _NAV 129 
#define  _QW 128 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

void LayerLEDSet(uint8_t layr) {

    switch (layr) {
        case _QW:
            rgblight_setrgb(0,20, 0); //  dim green
        break;
        case _LW:
            // deep purple
            rgblight_setrgb(20,0,35);
            break;
        case _HI:
            // light blue
           rgblight_setrgb(0,20,20);
            break;
        case _NAV:
            // Yellowy orange
            rgblight_setrgb(25,20,0); // brighter
            break;
        case _FKEYS:
         // RED
           rgblight_setrgb(20,0,0); // brighter
            break;
        default:
            rgblight_setrgb(20,2,20);//error
            break;
    }

 return;

}