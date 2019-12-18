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
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_3__ {int* confidence; int* focus; int focus_err; } ;
typedef  TYPE_1__ CameraState ;

/* Variables and functions */
 int NUM_FOCUS ; 
 int abs (int) ; 
 int max (int,int) ; 
 void* nan (char*) ; 

__attribute__((used)) static void parse_autofocus(CameraState *s, uint8_t *d) {
  int good_count = 0;
  int16_t max_focus = -32767;
  int avg_focus = 0;

  /*printf("FOCUS: ");
  for (int i = 0; i < 0x10; i++) {
    printf("%2.2X ", d[i]);
  }*/

  for (int i = 0; i < NUM_FOCUS; i++) {
    int doff = i*5+5;
    s->confidence[i] = d[doff];
    int16_t focus_t = (d[doff+1] << 3) | (d[doff+2] >> 5);
    if (focus_t >= 1024) focus_t = -(2048-focus_t);
    s->focus[i] = focus_t;
    //printf("%x->%d ", d[doff], focus_t);
    if (s->confidence[i] > 0x20) {
      good_count++;
      max_focus = max(max_focus, s->focus[i]);
      avg_focus += s->focus[i];
    }
  }

  //printf("\n");
  if (good_count < 4) {
    s->focus_err = nan("");
    return;
  }

  avg_focus /= good_count;

  // outlier rejection
  if (abs(avg_focus - max_focus) > 200) {
    s->focus_err = nan("");
    return;
  }

  s->focus_err = max_focus*1.0;
}