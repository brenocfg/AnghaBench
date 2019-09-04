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
 int V4L2_TUNER_MODE_LANG1 ; 
 int V4L2_TUNER_MODE_LANG2 ; 
 int V4L2_TUNER_MODE_MONO ; 
 int V4L2_TUNER_MODE_STEREO ; 

__attribute__((used)) static int amode2v4l(int amode)
{
    switch (amode) {
    case 0:
        return V4L2_TUNER_MODE_MONO;
    case 1:
        return V4L2_TUNER_MODE_STEREO;
    case 2:
        return V4L2_TUNER_MODE_LANG1;
    case 3:
        return V4L2_TUNER_MODE_LANG2;
    default:
        return -1;
    }
}