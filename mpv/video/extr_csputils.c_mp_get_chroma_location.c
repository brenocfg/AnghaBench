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
typedef  enum mp_chroma_location { ____Placeholder_mp_chroma_location } mp_chroma_location ;

/* Variables and functions */
 int MP_CHROMA_LEFT ; 

void mp_get_chroma_location(enum mp_chroma_location loc, int *x, int *y)
{
    *x = 0;
    *y = 0;
    if (loc == MP_CHROMA_LEFT)
        *x = -1;
}