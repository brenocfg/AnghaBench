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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 float M_PI ; 
 float cosf (float) ; 

__attribute__((used)) static uint8_t on_off_gradient(float t, float index, float num) {
    const float two_pi = M_PI * 2.0f;
    float normalized_index = (1.0f - index / (num - 1.0f)) * two_pi;
    float x = t * two_pi + normalized_index-M_PI;
    float v;
    if((2*M_PI) < x && x < (3*M_PI))
    {
      v = 0.5 * (cosf(x) + 1.0f);

    }
    else if(x >= (3*M_PI))
    {
      v = 0;
    }
    else
    {
      v = 1;
    }
    return (uint8_t)(255.0f * v);
}