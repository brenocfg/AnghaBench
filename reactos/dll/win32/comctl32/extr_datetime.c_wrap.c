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
 int INT_MAX ; 
 int INT_MIN ; 

__attribute__((used)) static int wrap(int val, int delta, int minVal, int maxVal)
{
    val += delta;
    if (delta == INT_MIN || val < minVal) return maxVal;
    if (delta == INT_MAX || val > maxVal) return minVal;
    return val;
}