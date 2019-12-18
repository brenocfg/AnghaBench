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
struct mp_aframe {int dummy; } ;

/* Variables and functions */
 scalar_t__ af_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int mp_aframe_get_channels (struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_get_format (struct mp_aframe*) ; 

int mp_aframe_get_planes(struct mp_aframe *frame)
{
    return af_fmt_is_planar(mp_aframe_get_format(frame))
           ? mp_aframe_get_channels(frame) : 1;
}