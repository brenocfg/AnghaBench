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
 int abs (int) ; 
 int min (int,int) ; 
 int rand () ; 

__attribute__((used)) static uint8_t get_random_wheel_index(uint8_t pos)
{
  uint8_t r = 0;
  uint8_t x = 0;
  uint8_t y = 0;
  uint8_t d = 0;

  while(d < 42) {
    r = rand() % 360;
    x = abs(pos - r);
    y = 360 - x;
    d = min(x, y);
  }

  return r;
}