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

double scc_time_to_timestamp(int hh, int mm, int ss, int ff)
{
    return (hh * 3600.0) + (mm * 60.0) + ss + (ff / 29.97);
}