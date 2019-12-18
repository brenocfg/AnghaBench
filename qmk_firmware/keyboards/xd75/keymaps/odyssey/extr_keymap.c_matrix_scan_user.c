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
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 int col ; 
 int /*<<< orphan*/ * led ; 
 scalar_t__ rc ; 
 int rgb ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int right ; 
 int /*<<< orphan*/  sethsv (int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ speed ; 
 int t ; 

void matrix_scan_user(void) {
  if (rgb==0) return; // Do nothing each tick right away if neither of animations enabled
  if (rgb==1) {
    if (rc == 0) {
      rc = speed;
      for(int i = 0; i<6; i++) {
        sethsv(42*((t+i)%6), 255, 255, (LED_TYPE *)&led[i]);
      }
      rgblight_set();
      t++; t = t % 6;
    }
  } else if (rgb==2) {
    if (rc == 0) {
      rc = speed;
      col = (col + 1) % 36;
      for (int i = 0; i<6; i++) {
        if (i==t)
          sethsv(42*(((col-1)/6)%6), 255, 255, (LED_TYPE *)&led[(right ? t : 5-t)]);
        else
          sethsv(0, 0, 0, (LED_TYPE *)&led[right ? i : 5-i]);
      }
      rgblight_set();
      t++; t = t % 6;
      if (t == 0) right = !right;
    }
  }
  rc--;
}