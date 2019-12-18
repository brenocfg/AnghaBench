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
 scalar_t__ isfinite (double) ; 
 float powf (float,float const) ; 

__attribute__((used)) static inline float db_to_mul(const float db)
{
	return isfinite((double)db) ? powf(10.0f, db / 20.0f) : 0.0f;
}