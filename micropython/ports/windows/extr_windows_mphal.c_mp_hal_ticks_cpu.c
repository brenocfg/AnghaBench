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
typedef  int /*<<< orphan*/  mp_uint_t ;
struct TYPE_3__ {int /*<<< orphan*/  LowPart; int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_1__*) ; 

mp_uint_t mp_hal_ticks_cpu(void) {
    LARGE_INTEGER value;
    QueryPerformanceCounter(&value);
#ifdef _WIN64
    return value.QuadPart;
#else
    return value.LowPart;
#endif
}