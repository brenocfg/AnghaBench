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
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_4__ {TYPE_2__ event; } ;
typedef  TYPE_1__ keyrecord_t ;
typedef  TYPE_2__ keyevent_t ;

/* Variables and functions */
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END ; 
 int LEFT ; 
 int /*<<< orphan*/  LSFT ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
#define  M_Q0 130 
#define  M_Q1 129 
#define  M_Q2 128 
 int P ; 
 int SPC ; 
 int /*<<< orphan*/  T (int) ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    switch (id) {
        case M_Q0:
            /* :( | ): */
            return event.pressed ?
                MACRO( D(LSFT), T(P), T(9), T(SPC), T(SPC), T(0), T(P), U(LSFT), T(LEFT), T(LEFT), T(LEFT), END ) :
                MACRO_NONE;
        case M_Q1:
            /* (: | :) */
            return event.pressed ?
                MACRO( D(LSFT), T(9), T(P), T(SPC), T(SPC), T(P), T(0), U(LSFT), T(LEFT), T(LEFT), T(LEFT), END ) :
                MACRO_NONE;
        case M_Q2:
            /* :) */
            return event.pressed ?
                MACRO( D(LSFT), T(P), T(0), U(LSFT), END ) :
                MACRO_NONE;
    }
    return MACRO_NONE;
}