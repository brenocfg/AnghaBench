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
typedef  int uint32_t ;

/* Variables and functions */
 int max3 (int,int,int) ; 
 int min3 (int,int,int) ; 

uint32_t grb2hsv(uint8_t g, uint8_t r, uint8_t b) {
    uint8_t m = min3(r, g, b);
    uint8_t M = max3(r, g, b);
    uint8_t delta = M - m;

    int hue = 0;
    int saturation = 0;
    int value = 0;

    if(delta == 0) {
        /* Achromatic case (i.e. grayscale) */
        hue = -1;          /* undefined */
        saturation = 0;
    } else {
        int h;

        if(r == M)
            h = ((g-b)*60) / delta;
        else if(g == M)
            h = ((b-r)*60) / delta + 120;
        else /*if(b == M)*/
            h = ((r-g)*60) / delta + 240;

        if(h < 0)
            h += 360;

        hue = h;

        /* The constatnt 8 is tuned to statistically cause as little
         * tolerated mismatches as possible in RGB -> HSV -> RGB conversion.
         * (See the unit test at the bottom of this file.)
         */
        saturation = (256*delta-8) / M;
    }
    value = M;

    uint32_t result = (hue << 16) | (saturation << 8) | value;
    return result;

}