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
 int MP_ARRAY_SIZE (int**) ; 
 int** planar_formats ; 

int af_fmt_to_planar(int format)
{
    for (int n = 0; n < MP_ARRAY_SIZE(planar_formats); n++) {
        if (planar_formats[n][1] == format)
            return planar_formats[n][0];
    }
    return format;
}