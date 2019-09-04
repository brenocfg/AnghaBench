#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int framesize; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ video_buffer_entry ;
struct TYPE_12__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_13__ {TYPE_2__ pix; } ;
struct TYPE_14__ {TYPE_3__ fmt; } ;
struct TYPE_17__ {int signal; } ;
struct TYPE_16__ {TYPE_4__ format; TYPE_7__ tuner; TYPE_1__* tv_param; int /*<<< orphan*/  video_fd; } ;
typedef  TYPE_6__ priv_t ;
struct TYPE_11__ {int automute; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDIOC_G_TUNER ; 
 int /*<<< orphan*/  fcc_vl2mp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_blank_frame (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  set_mute (TYPE_6__*,int) ; 
 scalar_t__ v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static inline void copy_frame(priv_t *priv, video_buffer_entry *dest, unsigned char *source,int len)
{
    dest->framesize=len;
    if(priv->tv_param->automute>0){
        if (v4l2_ioctl(priv->video_fd, VIDIOC_G_TUNER, &priv->tuner) >= 0) {
            if(priv->tv_param->automute<<8>priv->tuner.signal){
                fill_blank_frame(dest->data,dest->framesize,fcc_vl2mp(priv->format.fmt.pix.pixelformat));
                set_mute(priv,1);
                return;
            }
        }
        set_mute(priv,0);
    }
    memcpy(dest->data, source, len);
}