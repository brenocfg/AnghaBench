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
typedef  scalar_t__ u_int8_t ;

/* Variables and functions */

__attribute__((used)) static inline bool
type_match(u_int8_t min, u_int8_t max, u_int8_t type, bool invert)
{
	return (type >= min && type <= max) ^ invert;
}