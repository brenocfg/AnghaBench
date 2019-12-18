#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * cp; int /*<<< orphan*/ * cpend; } ;
typedef  TYPE_1__ CompilerState ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  JS7_ISDEC (int /*<<< orphan*/ ) ; 
 int JS7_UNDEC (int /*<<< orphan*/ ) ; 
 int OVERFLOW_VALUE ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static UINT
GetDecimalValue(WCHAR c, UINT max, UINT (*findMax)(CompilerState *state),
                CompilerState *state)
{
    UINT value = JS7_UNDEC(c);
    BOOL overflow = (value > max && (!findMax || value > findMax(state)));

    /* The following restriction allows simpler overflow checks. */
    assert(max <= ((UINT)-1 - 9) / 10);
    while (state->cp < state->cpend) {
        c = *state->cp;
        if (!JS7_ISDEC(c))
            break;
        value = 10 * value + JS7_UNDEC(c);
        if (!overflow && value > max && (!findMax || value > findMax(state)))
            overflow = TRUE;
        ++state->cp;
    }
    return overflow ? OVERFLOW_VALUE : value;
}