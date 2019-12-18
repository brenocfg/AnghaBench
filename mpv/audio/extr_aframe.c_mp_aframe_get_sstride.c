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
 scalar_t__ af_fmt_is_planar (int) ; 
 int af_fmt_to_bytes (int) ; 
 int mp_aframe_get_channels (struct mp_aframe*) ; 
 int mp_aframe_get_format (struct mp_aframe*) ; 

size_t mp_aframe_get_sstride(struct mp_aframe *frame)
{
    int format = mp_aframe_get_format(frame);
    return af_fmt_to_bytes(format) *
           (af_fmt_is_planar(format) ? 1 : mp_aframe_get_channels(frame));
}