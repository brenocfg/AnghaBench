#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  i; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 TYPE_1__ numOnce ; 

void
myfunc(void)
{
  EnterCriticalSection(&numOnce.cs);
  numOnce.i++;
  LeaveCriticalSection(&numOnce.cs);
  /* Simulate slow once routine so that following threads pile up behind it */
  Sleep(100);
}