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

/* Variables and functions */
 char const* strerror (int) ; 

const char *strerror_x(int x)
{
#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif
#undef strerror
    return strerror(x);
}