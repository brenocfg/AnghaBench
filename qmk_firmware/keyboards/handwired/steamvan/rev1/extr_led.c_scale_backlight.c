#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_2__ {int level; } ;

/* Variables and functions */
 int BACKLIGHT_LEVELS ; 
 TYPE_1__ kb_backlight_config ; 

__attribute__((used)) static inline uint16_t scale_backlight(uint16_t v) {
  return v / BACKLIGHT_LEVELS * kb_backlight_config.level;
}