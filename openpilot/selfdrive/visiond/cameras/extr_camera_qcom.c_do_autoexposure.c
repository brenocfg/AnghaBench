#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float cur_exposure_frac; float cur_gain_frac; } ;
typedef  TYPE_1__ CameraState ;

/* Variables and functions */
 float pow (double,float const) ; 
 int /*<<< orphan*/  set_exposure (TYPE_1__*,float,float) ; 

__attribute__((used)) static void do_autoexposure(CameraState *s, float grey_frac) {
  const float target_grey = 0.3;

  float new_exposure = s->cur_exposure_frac;
  new_exposure *= pow(1.05, (target_grey - grey_frac) / 0.05 );
  //LOGD("diff %f: %f to %f", target_grey - grey_frac, s->cur_exposure_frac, new_exposure);

  float new_gain = s->cur_gain_frac;
  if (new_exposure < 0.10) {
    new_gain *= 0.95;
  } else if (new_exposure > 0.40) {
    new_gain *= 1.05;
  }

  set_exposure(s, new_exposure, new_gain);
}