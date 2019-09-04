#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int sizeimage; } ;
struct TYPE_9__ {TYPE_2__ pix; } ;
struct TYPE_10__ {TYPE_3__ fmt; } ;
struct TYPE_11__ {size_t video_head; TYPE_4__ format; TYPE_1__* video_ringbuffer; scalar_t__ video_cnt; } ;
typedef  TYPE_5__ priv_t ;
struct TYPE_7__ {int framesize; } ;

/* Variables and functions */

__attribute__((used)) static int get_video_framesize(priv_t *priv)
{
    /*
      this routine will be called before grab_video_frame
      thus let's return topmost frame's size
    */
    if (priv->video_cnt)
        return priv->video_ringbuffer[priv->video_head].framesize;
    /*
      no video frames yet available. i don't know what to do in this case,
      thus let's return some fallback result (for compressed format this will be
      maximum allowed frame size.
    */
    return priv->format.fmt.pix.sizeimage;
}