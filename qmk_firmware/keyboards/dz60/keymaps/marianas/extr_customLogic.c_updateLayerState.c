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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  FN_LAYER ; 
#define  FN_QT 128 
 int /*<<< orphan*/  TIMER_DIFF_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activateRelativity () ; 
 int /*<<< orphan*/  deactivateRelativity () ; 
 int didFn ; 
 int /*<<< orphan*/  fnTimeout ; 
 int /*<<< orphan*/  fnTimer ; 
 int isFn ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

bool updateLayerState(uint16_t keycode, keyrecord_t *record)
{

  if (record->event.pressed)
  {
    switch (keycode)
    {
      case FN_QT:
        fnTimer = timer_read();
        layer_on(FN_LAYER);
        isFn = true;
        return false;
    }
    if (isFn)
    {
      didFn = true;
      return true;
    }
  }
  else
  {
    switch(keycode)
    {
      case FN_QT:
        layer_off(FN_LAYER);
        if (!didFn)
        {
          #if fnTimeout
          if (TIMER_DIFF_16(timer_read(), fnTimer) <= fnTimeout)
          {
            activateRelativity();
          }
          else
          {
            deactivateRelativity();
          }
          #else
          activateRelativity();
          #endif
        }
        didFn = false;
        isFn = false;
        return false;
    }
  }
  return true;
}