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
struct TYPE_3__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_rgb_b ; 
 int /*<<< orphan*/  backlight_rgb_g ; 
 int /*<<< orphan*/  backlight_rgb_r ; 
 int /*<<< orphan*/  backlight_set_rgb (TYPE_1__**) ; 

void backlight_toggle_rgb(bool enabled)
{
  if(enabled) {
    uint8_t rgb[17][3] = {
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b},
      {backlight_rgb_r, backlight_rgb_g, backlight_rgb_b}
    };
    backlight_set_rgb(rgb);
  } else {
    uint8_t rgb[17][3] = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
    };
    backlight_set_rgb(rgb);
  }
}