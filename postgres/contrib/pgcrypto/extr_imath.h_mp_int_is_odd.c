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
typedef  TYPE_1__* mp_int ;
struct TYPE_3__ {int* digits; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
mp_int_is_odd(mp_int z)
{
	return (z->digits[0] & 1) != 0;
}