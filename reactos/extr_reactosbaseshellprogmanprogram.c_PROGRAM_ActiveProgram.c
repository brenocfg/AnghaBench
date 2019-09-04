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
struct TYPE_3__ {int /*<<< orphan*/ * hActiveProgram; int /*<<< orphan*/  hWnd; } ;
typedef  int /*<<< orphan*/  PROGRAM ;
typedef  TYPE_1__ PROGGROUP ;

/* Variables and functions */
 scalar_t__ IsIconic (int /*<<< orphan*/ ) ; 

PROGRAM* PROGRAM_ActiveProgram(PROGGROUP* hGroup)
{
    if (!hGroup) return NULL;
    if (IsIconic(hGroup->hWnd)) return NULL;
    return hGroup->hActiveProgram;
}