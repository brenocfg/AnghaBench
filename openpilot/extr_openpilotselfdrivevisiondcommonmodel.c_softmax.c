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

/* Variables and functions */
 float FLT_MAX ; 
 float expf (float const) ; 

void softmax(const float* input, float* output, size_t len) {
  float max_val = -FLT_MAX;
  for(int i = 0; i < len; i++) {
    const float v = input[i];
    if( v > max_val ) {
      max_val = v;
    }
  }

  float denominator = 0;
  for(int i = 0; i < len; i++) {
    float const v = input[i];
    float const v_exp = expf(v - max_val);
    denominator += v_exp;
    output[i] = v_exp;
  }

  const float inv_denominator = 1. / denominator;
  for(int i = 0; i < len; i++) {
    output[i] *= inv_denominator;
  }

}