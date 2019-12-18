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
struct TYPE_3__ {int dwSize; int /*<<< orphan*/  dwFadeTime; int /*<<< orphan*/  dwFadeLevel; int /*<<< orphan*/  dwAttackTime; int /*<<< orphan*/  dwAttackLevel; } ;
typedef  TYPE_1__* LPCDIENVELOPE ;
typedef  int /*<<< orphan*/  DIENVELOPE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static void _dump_DIENVELOPE(LPCDIENVELOPE env)
{
    if (env->dwSize != sizeof(DIENVELOPE)) {
        WARN("Non-standard DIENVELOPE structure size %d.\n", env->dwSize);
    }
    TRACE("Envelope has attack (level: %d time: %d), fade (level: %d time: %d)\n",
          env->dwAttackLevel, env->dwAttackTime, env->dwFadeLevel, env->dwFadeTime);
}