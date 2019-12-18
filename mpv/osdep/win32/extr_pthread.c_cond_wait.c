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
struct TYPE_4__ {int /*<<< orphan*/  srw; int /*<<< orphan*/  cs; } ;
struct TYPE_5__ {TYPE_1__ lock; scalar_t__ use_cs; } ;
typedef  TYPE_2__ pthread_mutex_t ;
typedef  int /*<<< orphan*/  pthread_cond_t ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ SleepConditionVariableCS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SleepConditionVariableSRW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cond_wait(pthread_cond_t *restrict cond,
                     pthread_mutex_t *restrict mutex,
                     DWORD ms)
{
    BOOL res;
    if (mutex->use_cs) {
        res = SleepConditionVariableCS(cond, &mutex->lock.cs, ms);
    } else {
        res = SleepConditionVariableSRW(cond, &mutex->lock.srw, ms, 0);
    }
    return res ? 0 : ETIMEDOUT;
}