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
typedef  int /*<<< orphan*/  macro_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 int A ; 
 int C ; 
 int E ; 
 int /*<<< orphan*/  END ; 
 int ENT ; 
 int L ; 
 int M ; 
 int /*<<< orphan*/  const* MACRODOWN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int MINS ; 
 int S ; 
 int SPC ; 
 int /*<<< orphan*/  T (int) ; 
#define  _CUS1 130 
#define  _CUS2 129 
#define  _MOB 128 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
    case _MOB: // Your mobile# here.
	return MACRODOWN(T(1), T(2), T(3), T(MINS),
			 T(1), T(2), T(3), T(MINS),
			 T(1), T(2), T(3), T(4),
			 END);
    case _CUS1: // Your custom macro 1
	return MACRODOWN(T(E), T(M), T(A), T(C), T(S), T(SPC), END);
    case _CUS2: // Your custom macro 2
	return MACRODOWN(T(L), T(S), T(SPC), T(MINS), T(L), T(ENT), END);
    };
    return MACRO_NONE;
}