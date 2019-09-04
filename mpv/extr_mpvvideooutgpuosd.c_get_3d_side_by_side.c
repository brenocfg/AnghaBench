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
#define  MP_STEREO3D_AB2L 131 
#define  MP_STEREO3D_AB2R 130 
#define  MP_STEREO3D_SBS2L 129 
#define  MP_STEREO3D_SBS2R 128 

__attribute__((used)) static void get_3d_side_by_side(int stereo_mode, int div[2])
{
    div[0] = div[1] = 1;
    switch (stereo_mode) {
    case MP_STEREO3D_SBS2L:
    case MP_STEREO3D_SBS2R: div[0] = 2; break;
    case MP_STEREO3D_AB2R:
    case MP_STEREO3D_AB2L:  div[1] = 2; break;
    }
}