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
typedef  double int64_t ;

/* Variables and functions */
 double INT64_MAX ; 
 double INT64_MIN ; 

__attribute__((used)) static bool same_as_int64(double d)
{
    // The range checks also validly filter inf and nan, so behavior is defined
    return d >= INT64_MIN && d <= INT64_MAX && d == (int64_t)d;
}