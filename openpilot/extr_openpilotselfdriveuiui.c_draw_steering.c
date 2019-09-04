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
typedef  int /*<<< orphan*/  UIState ;

/* Variables and functions */
 int asin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clamp (int,double,double) ; 
 int tan (int) ; 

__attribute__((used)) static void draw_steering(UIState *s, float curvature) {
  float points[50];
  for (int i = 0; i < 50; i++) {
    float y_actual = i * tan(asin(clamp(i * curvature, -0.999, 0.999)) / 2.);
    points[i] = y_actual;
  }

  // ui_draw_lane_edge(s, points, 0.0, nvgRGBA(0, 0, 255, 128), 5);
}