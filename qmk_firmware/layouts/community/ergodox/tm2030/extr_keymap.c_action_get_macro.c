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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  FNLR ; 
 int /*<<< orphan*/  I (int) ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
#define  MDBL0 129 
#define  MFNLR 128 
 int /*<<< orphan*/  NUMR ; 
 int /*<<< orphan*/  P0 ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_invert (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
        case MDBL0:
            if (record->event.pressed) {
              return MACRO( I(25), T(P0), T(P0), END );
            }
        break;
        case MFNLR:
            layer_invert(NUMR);
            layer_invert(FNLR);
            break;
    }
    return MACRO_NONE;
}