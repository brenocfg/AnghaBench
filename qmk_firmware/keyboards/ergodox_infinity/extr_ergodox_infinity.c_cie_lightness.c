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
typedef  float uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t cie_lightness(uint16_t v) {
    // The CIE 1931 formula for lightness
    // Y = luminance (output) 0-1
    // L = lightness input 0 - 100

    // Y = (L* / 902.3)           if L* <= 8
    // Y = ((L* + 16) / 116)^3    if L* > 8

    float l =  100.0f * (v / 65535.0f);
    float y = 0.0f;
    if (l <= 8.0f) {
       y = l / 902.3;
    }
    else {
        y = ((l + 16.0f) / 116.0f);
        y = y * y * y;
        if (y > 1.0f) {
            y = 1.0f;
        }
    }
    return y * 65535.0f;
}