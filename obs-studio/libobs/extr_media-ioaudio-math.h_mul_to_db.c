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
 float INFINITY ; 
 float log10f (float const) ; 

__attribute__((used)) static inline float mul_to_db(const float mul)
{
	return (mul == 0.0f) ? -INFINITY : (20.0f * log10f(mul));
}