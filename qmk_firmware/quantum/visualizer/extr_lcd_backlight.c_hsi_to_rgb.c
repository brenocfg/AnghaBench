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
typedef  int uint16_t ;

/* Variables and functions */
 float cos (float) ; 
 float cosf (float) ; 
 float fmodf (float,float) ; 

__attribute__((used)) static void hsi_to_rgb(float h, float s, float i, uint16_t* r_out, uint16_t* g_out, uint16_t* b_out) {
    unsigned int r, g, b;
    h = fmodf(h, 360.0f);                         // cycle h around to 0-360 degrees
    h = 3.14159f * h / 180.0f;                    // Convert to radians.
    s = s > 0.0f ? (s < 1.0f ? s : 1.0f) : 0.0f;  // clamp s and i to interval [0,1]
    i = i > 0.0f ? (i < 1.0f ? i : 1.0f) : 0.0f;

    // Math! Thanks in part to Kyle Miller.
    if (h < 2.09439f) {
        r = 65535.0f * i / 3.0f * (1.0f + s * cos(h) / cosf(1.047196667f - h));
        g = 65535.0f * i / 3.0f * (1.0f + s * (1.0f - cosf(h) / cos(1.047196667f - h)));
        b = 65535.0f * i / 3.0f * (1.0f - s);
    } else if (h < 4.188787) {
        h = h - 2.09439;
        g = 65535.0f * i / 3.0f * (1.0f + s * cosf(h) / cosf(1.047196667f - h));
        b = 65535.0f * i / 3.0f * (1.0f + s * (1.0f - cosf(h) / cosf(1.047196667f - h)));
        r = 65535.0f * i / 3.0f * (1.0f - s);
    } else {
        h = h - 4.188787;
        b = 65535.0f * i / 3.0f * (1.0f + s * cosf(h) / cosf(1.047196667f - h));
        r = 65535.0f * i / 3.0f * (1.0f + s * (1.0f - cosf(h) / cosf(1.047196667f - h)));
        g = 65535.0f * i / 3.0f * (1.0f - s);
    }
    *r_out = r > 65535 ? 65535 : r;
    *g_out = g > 65535 ? 65535 : g;
    *b_out = b > 65535 ? 65535 : b;
}