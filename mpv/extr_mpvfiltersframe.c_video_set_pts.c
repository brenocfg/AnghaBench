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
struct mp_image {double pts; } ;

/* Variables and functions */

__attribute__((used)) static void video_set_pts(void *data, double pts)
{
    ((struct mp_image *)data)->pts = pts;
}