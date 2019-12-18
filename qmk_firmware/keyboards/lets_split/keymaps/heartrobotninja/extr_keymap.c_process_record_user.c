#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  AUX 131 
#define  COLE 130 
#define  LOWER 129 
#define  RAISE 128 
 int /*<<< orphan*/  _AUX ; 
 unsigned long _COLE ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  case COLE:
    if (record->event.pressed)
    {
      persistent_default_layer_set(1UL << _COLE);
    }
    return false;
    break;
  case LOWER:
    if (record->event.pressed)
    {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _AUX);
    }
    else
    {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _AUX);
    }
    return false;
    break;
  case RAISE:
    if (record->event.pressed)
    {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _AUX);
    }
    else
    {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _AUX);
    }
    return false;
    break;
  case AUX:
    if (record->event.pressed)
    {
      layer_on(_AUX);
    }
    else
    {
      layer_off(_AUX);
    }
    return false;
    break;
  }
  return true;
}