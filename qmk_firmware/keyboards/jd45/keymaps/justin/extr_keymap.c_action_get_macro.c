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
 int ENT ; 
 int /*<<< orphan*/  I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
#define  PSWD1 130 
#define  PSWD2 129 
#define  PSWD3 128 
 int /*<<< orphan*/  T (int) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id)
    {
    case PSWD1:
        return (record->event.pressed ? MACRO(I(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(ENT), END) : MACRO_NONE);
    case PSWD2:
        return (record->event.pressed ? MACRO(I(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(ENT), END) : MACRO_NONE);
    case PSWD3:
        return (record->event.pressed ? MACRO(I(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(ENT), END) : MACRO_NONE);
        //case VOLUP:
        //    return (record->event.pressed ?
        //            MACRO( D(VOLU), U(VOLU), END ) :
        //            MACRO_NONE );
        //case ALT_TAB:
        //    return (record->event.pressed ?
        //            MACRO( D(LALT), D(TAB), END ) :
        //            MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}