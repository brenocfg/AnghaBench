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
#define  CFLEX 129 
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END ; 
 int const EQL ; 
#define  GRV 128 
 int /*<<< orphan*/  LSFT ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  RALT ; 
 int const SPC ; 
 int /*<<< orphan*/  T (int const) ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case GRV: // macro to print accent grave
            return (record->event.pressed ?
                    MACRO( D(LSFT), T(EQL), U(RALT), T(SPC), END) :
                    MACRO_NONE );
        case CFLEX: // print accent circonflex
            return (record->event.pressed ?
                    MACRO( T(GRV), T(SPC), END ) :
                    MACRO_NONE );
      }
    return MACRO_NONE;
}